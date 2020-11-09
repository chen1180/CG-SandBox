#version 330 core

in VS_OUT
{
	vec2 texCoord;
	vec3 normal,tangent;
	vec4 color;
	vec3 fragPos;
	//vec4 fragPosLightSpace; 
	
} fs_in;

struct Light {
    vec4 position ;
    vec4 direction;
    vec4 color ;
    float type; //0: Directional light 1: Point light 2: Spot light
    float intensity;
    float radius;
    float angle;
};

#define MAXLIGHTS 32
layout(std140, binding = 1) uniform uLights {
    Light lights [ MAXLIGHTS ];
    int lightNum;
};

#define MaxShadowMap 16
layout(std140, binding = 2) uniform uLightTransformMatrix {
     mat4 uLightViewProj[MaxShadowMap];
     int ShadowMapCount;

};

const float screenGamma = 2.2;
const float PI = 3.14159265359;

uniform vec3 viewPos; 
//uniform vec3 lightColor;
uniform sampler2D shadowMap[MaxShadowMap];
uniform samplerCube skyBox;

uniform vec3  albedo=vec3(1.0f,0.0f,0.0f);
uniform float metallic=0.1f;
uniform float roughness=0.3f;
uniform float ao=0.5f;


out vec4 FragColor;

float windowFuncAttenuation(float radius);

float DistributionGGX(vec3 N, vec3 H, float roughness);

float GeometrySchlickGGX(float NdotV, float roughness);

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);

vec3 fresnelSchlick(float cosTheta, vec3 F0);

float ShadowCalculation(vec4 fragPosLightSpace,vec3 lightPos,int shadowMapIndex);

void main()
{
    vec3 N = normalize(fs_in.normal); 
    vec3 V = normalize(viewPos - fs_in.fragPos);

    vec3 F0 = vec3(0.04); 
    F0      = mix(F0, albedo, metallic);

    vec3 Lo=vec3(0.0f);
    float shadow=0.0f;
    for (int i=0;i<lightNum;i++){

        vec3 lightPos=lights[i].position.xyz;
        vec3 lightColor=lights[i].color.rgb*lights[i].intensity;

        vec3 L = normalize(lightPos - fs_in.fragPos);
        vec3 H = normalize(V + L);
       
        float attenuation=1.0f;
        float dist=length(lightPos - fs_in.fragPos);
        
        // Attenuation
		float atten = lights[i].radius / (pow(dist, 2.0) + 1.0);
        attenuation=atten*windowFuncAttenuation(dist);
        vec3 radiance=lightColor*attenuation;

        
        float NDF = DistributionGGX(N, H, roughness);       
        float G   = GeometrySmith(N, V, L, roughness); 
        vec3 F  = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  


        float NdotL = max(dot(N, L), 0.0);        
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;


        vec4 fragPosLightSpace=uLightViewProj[i]* vec4(fs_in.fragPos, 1.0);
        shadow += ShadowCalculation(fragPosLightSpace,lightPos,i);
        
    }
    shadow=clamp(shadow,0.0,1.0);
    
    vec3 ambient = vec3(0.1) * albedo * ao;

    
    vec3 color = ambient + Lo;	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
    //vec3 colorLinear = ambient +  (1.0f-shadow)*Lo;  
    //vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));
    //FragColor = vec4(colorGammaCorrected,1.0f);
}

float ShadowCalculation(vec4 fragPosLightSpace,vec3 lightPos,int shadowMapIndex)
{
     // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z>1.0f) 
        return 0.0f;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap[shadowMapIndex], projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
     float shadow = 0.0;
    // check whether current frag pos is in shadow
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);
    //PCF
    float bias = max(0.05 * (1.0 - dot(fs_in.normal, lightDir)), 0.005);  
  
    vec2 texelSize = 1.0 / textureSize(shadowMap[shadowMapIndex], 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap[shadowMapIndex], projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    return shadow;
}

float windowFuncAttenuation(float radius){

    const float radiusMax=50.0f;
    float value=1-pow(radius/radiusMax,4.0f);
    return pow(max(value,0.0),2);

}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}  

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

