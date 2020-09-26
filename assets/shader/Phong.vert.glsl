#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec2 aTexCoord; 
layout(location = 3) in vec3 aNormal; 
layout(location = 4) in vec3 aTangent; 

out VS_OUT
{
	vec2 texCoord;
	vec3 normal,tangent;
	vec4 color;
	vec3 fragPos;
	//vec4 fragPosLightSpace; 
	
} vs_out;

layout(std140, binding = 0) uniform uTransformMatrix {
     mat4 uView;
	 mat4 uProjection;
};

uniform mat4 uModel;

void main()
{
   	gl_Position =uProjection*uView*uModel* vec4(aPos, 1.0);
    vs_out.texCoord = aTexCoord; // set ourColor to the input color we got from the vertex data
	vs_out.tangent=aTangent;
	vs_out.color=aColor;
	vec4 fragPos4=uModel * vec4(aPos, 1.0f);
	vs_out.fragPos=vec3(fragPos4) / fragPos4.w;
	//vs_out.fragPosLightSpace=uLightViewProj[UShadowMapIndex]* vec4(vs_out.fragPos, 1.0);
    vs_out.normal =transpose(inverse(mat3(uModel))) * aNormal;

}