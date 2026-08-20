#version 330 core
out vec4 FragColour; // output a color to the framebuffer

void main()
{
	FragColour = vec4(0.5f, 0.82f, 0.11f, 1.0f); 
	// the colour values are in the range of 0.0 to 1.0, so this is a pink colour, end number is alpha value

}	