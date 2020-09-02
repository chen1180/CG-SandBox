#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec2 aTexCoord; 
layout(location = 3) in vec3 aNormal; 
layout(location = 4) in vec3 aTangent; 

out vec2 texCoord;
out vec3 normal,tangent;
out vec4 color;
out vec3 fragPos;
out vec4 fragPosLightSpace; 
uniform mat4 uView,uProjection,uModel;
uniform mat4 uLightProjection;
uniform mat4 uLightView;

void main()
{
   	gl_Position =uProjection*uView*uModel* vec4(aPos, 1.0);
    texCoord = aTexCoord; // set ourColor to the input color we got from the vertex data
	tangent=aTangent;
	color=aColor;
	fragPos=vec3(uModel * vec4(aPos, 1.0f));
	fragPosLightSpace=uLightProjection* uLightView* vec4(fragPos, 1.0);
    normal = mat3(transpose(inverse(uModel))) * aNormal;  

}