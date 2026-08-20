#version 330 core
layout (location = 0) in vec3 aPos; // in the layout location 0 we have the position of the vertex

void main()
{
	gl_Position = vec4(aPos, 1.0); // set the position of the vertex in clip space, gl_Position must be set in the vertex shader
}