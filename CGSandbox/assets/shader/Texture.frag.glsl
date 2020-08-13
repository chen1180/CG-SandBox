#version 330 core

in vec2 texCoord;
in vec4 color;
in float textureIndex;

out vec4 FragColor;
uniform sampler2D u_Texture[32];
void main()
{
	FragColor =texture(u_Texture[int(textureIndex)],texCoord)*color;
}
