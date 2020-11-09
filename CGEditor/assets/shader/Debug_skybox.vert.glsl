#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout(std140, binding = 0) uniform uTransformMatrix {
     mat4 uView,uProjection;
};

void main()
{
    TexCoords = aPos;
    //Drop the translation column of view matrix.
    vec4 pos = uProjection * mat4(mat3(uView)) * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  