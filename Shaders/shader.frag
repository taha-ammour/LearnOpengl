#version 330

out vec4 colour;

in vec4 Vcol;
in vec2 TexCoord;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

	colour = texture(theTexture, TexCoord) * ambientColour;
}