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


uniform vec3 viewPos; 
//uniform vec3 lightColor;
uniform sampler2D shadowMap[MaxShadowMap];
uniform samplerCube skyBox;

out vec4 FragColor;
//uniform vec3 lightPos; 

//uLightViewProj[UShadowMapIndex]* vec4(vs_out.fragPos, 1.0);

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


const float screenGamma = 2.2;

void main()
{
    vec3 ambientColor=vec3(0.1f);
    vec3 diffuseColor=vec3(0.0f);
    vec3 specularColor=vec3(0.0f);
    float shadow=0.0f;
    for (int i=0;i<lightNum;i++){
        vec3 lightPos=lights[i].position.xyz;
        vec3 lightColor=lights[i].color.rgb;

        // diffuse 
        vec3 norm = normalize(fs_in.normal);
        vec3 lightDir = normalize(lightPos - fs_in.fragPos);
        float diff = max(dot(lightDir,norm), 0.0);
        diffuseColor += diff * lightColor;
        // specular
        float specularStrength = 0.8;
        vec3 viewDir = normalize(viewPos - fs_in.fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        //vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
        specularColor += specularStrength * spec * lightColor;  
        
        vec4 fragPosLightSpace=uLightViewProj[i]* vec4(fs_in.fragPos, 1.0);
        shadow += ShadowCalculation(fragPosLightSpace,lightPos,i);
    }
    shadow=clamp(shadow,0.0,1.0);
    vec3 colorLinear = (ambientColor +  (1.0f-shadow)*(diffuseColor + specularColor)) * fs_in.color.rgb;  
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));
    FragColor = vec4(colorGammaCorrected,1.0f);
}