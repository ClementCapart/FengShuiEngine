#version 330 core

layout(location = 0) in vec3 VertexPosition_ModelSpace;

void main()
{
	gl_Position.xyz = VertexPosition_ModelSpace;
	gl_Position.w = 1.0f;
}