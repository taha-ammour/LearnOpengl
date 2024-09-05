#version 330

out vec4 colour;

in vec4 Vcol;

void main()
{
	colour = Vcol;
}