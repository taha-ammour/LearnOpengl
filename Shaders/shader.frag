#version 330

out vec4 colour;

in vec4 Vcol;
in vec2 TexCoord;

uniform sampler2D theTexture;

void main()
{
	colour = texture(theTexture, TexCoord);
}