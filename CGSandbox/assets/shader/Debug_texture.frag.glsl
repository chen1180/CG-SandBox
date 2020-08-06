#version 330 core

out vec4 FragColor;
in vec2 textCoord;
uniform sampler2D uTexture;
void main()
{
	FragColor = texture2D(uTexture,textCoord);
}