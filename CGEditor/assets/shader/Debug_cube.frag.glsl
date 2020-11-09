#version 330 core

in vec2 texCoord;
in vec3 normal,tangent;
in vec4 color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(vec2(texCoord),1.0f,1.0f);
}
