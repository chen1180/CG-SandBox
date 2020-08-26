#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal,tangent,fragPos;
in vec4 color;


uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform samplerCube skybox;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    //reflection
    vec3 I = normalize(fragPos - viewPos);
    vec3 Reflect = reflect(I, normalize(normal));
    vec3 reflectColor= texture(skybox, Reflect).rgb;
    //refraction
    float ratio = 1.00 / 1.52;
    vec3 Refract= refract(I, normalize(normal), ratio);
    vec3 refractColor = texture(skybox,Refract).rgb;
    vec3 result = (ambient + diffuse + specular) *objectColor;
    FragColor =vec4(reflectColor*refractColor,1.0f);
} 