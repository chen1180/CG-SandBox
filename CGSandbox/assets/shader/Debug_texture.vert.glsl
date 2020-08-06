#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec2 aTextCoord; // the color variable has attribute position 1

out vec2 textCoord;
uniform mat4 ViewProjTransform;
void main()
{
	gl_Position =ViewProjTransform* vec4(aPos, 1.0);
	textCoord = aTextCoord; // set ourColor to the input color we got from the vertex data
}