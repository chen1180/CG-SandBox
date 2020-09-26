#version 330 core
layout (location = 0) in vec3 position;

#define MaxShadowMap 16
layout(std140, binding = 0) uniform uLightTransformMatrix {
     mat4 uLightViewProj[MaxShadowMap];
     int ShadowMapCount;

};

uniform mat4 uModel;
uniform int uLightIndex;

void main()
{
    gl_Position = uLightViewProj[uLightIndex]* uModel * vec4(position, 1.0f);
}