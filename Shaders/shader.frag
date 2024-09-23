#version 330

out vec4 colour;

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

in vec4 Vcol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 fragPos;

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;


vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;

		float diffuseFactor = max(dot(normalize(Normal),normalize(direction)), 0.0f);
		vec4 diffuseColour = vec4(light.colour,1.0f) * light.diffuseIntensity * diffuseFactor ;

		vec4 specularColour = vec4(0.0f,0.0f,0.0f,0.0f);

		if(diffuseFactor > 0.0f)
		{
			vec3 fragToEye = normalize(eyePosition - fragPos);
			vec3 reflectedVertex = normalize(reflect(direction,normalize(Normal)));

			float specularFactor = dot(fragToEye,reflectedVertex);
			if(specularFactor > 0.0f)
			{
				specularFactor = pow(specularFactor, material.shininess);
				specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
			}
		}
	return (ambientColour + diffuseColour + specularColour);
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.base,directionalLight.direction);
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = fragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 colour = CalcLightByDirection(pLight.base, direction);
	float attenuation = max(pLight.exponent * distance * distance + pLight.linear * distance + pLight.constant,0.001f);
	return (colour/attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(fragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);

	if(slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base);

		return colour * (1.0f - (1.0f - slFactor) * (1.0f/(1.0f - sLight.edge)));
	}
	else
	{
		return vec4(0.0f,0.0f,0.0f,0.0f);
	}
}

vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0.0f,0.0f,0.0f,0.0f);
	for(int i=0; i <pointLightCount;i++)
	{
		totalColour +=	CalcPointLight(pointLights[i]);
	}
	return totalColour;
}

vec4 CalcSpotLights()
{
	vec4 totalColour = vec4(0.0f,0.0f,0.0f,0.0f);
	for(int i=0; i <spotLightCount;i++)
	{
		totalColour +=	CalcSpotLight(spotLights[i]);
	}
	return totalColour;
}

void main()
{
	vec4 finalColor = CalcDirectionalLight();
	finalColor += CalcPointLights();
	finalColor += CalcSpotLights();

	colour = texture(theTexture, TexCoord) * finalColor;
}