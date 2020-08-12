#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec2 aTexCoord; 

out vec2 texCoord;
out vec4 color;
uniform mat4 u_ViewMatrix,u_ProjectionMatrix;
void main()
{
	gl_Position =u_ProjectionMatrix*u_ViewMatrix* vec4(aPos, 1.0);
	texCoord = aTexCoord; // set ourColor to the input color we got from the vertex data
	color=aColor;
}