#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "CommonValues.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
private:
	int pointLightCount;
	int spotLightCount;

	GLuint ShaderID, uniformModel, uniformProjection, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess;

	struct 
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	}uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	}uniformPointLight[MAX_POINT_LIGHTS];

	GLuint uniformSpotLightCount;

	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
public:
	Shader();

	void CreateShaderFromString(const char* vertexCode, const char* fragmentCode);
	void CreateShaderFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint get_ProjectionLocation();
	GLuint get_ModelLocation();
	GLuint get_ViewLocation();
	GLuint get_ambientIntensityLocation();
	GLuint get_colorLocation();
	GLuint get_diffuseIntensityLocation();
	GLuint get_directionLocation();
	GLuint get_specularIntensityLocation();
	GLuint get_shininessLocation();
	GLuint get_eyePositionLocation();

	void set_DirectionalLight(DirectionalLight* dLight);
	void set_PointLight(PointLight* pLight, unsigned int lightCount);
	void set_SpotLight(SpotLight* sLight, unsigned int lightCount);


	void useShader();
	void ClearShader();

	~Shader();
};

