#include "Shader.h"


Shader::Shader()
{
	ShaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
	uniformDirectionalLight.uniformColour = 0;
	uniformDirectionalLight.uniformAmbientIntensity = 0;
	uniformDirectionalLight.uniformDirection = 0;
	uniformDirectionalLight.uniformDiffuseIntensity = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;
	uniformEyePosition = 0;

	pointLightCount = 0;
	uniformPointLightCount = 0;
}

void Shader::CreateShaderFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateShaderFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	CompileShader(vertexCode, fragmentCode);

}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream filestream(fileLocation, std::ios::in);

	if (!filestream.is_open())
	{
		std::cerr << "failed to read " << fileLocation << " file doesnt exist !!!"<<std::endl;
		return "";
	}

	std::string line = "";
	while (!filestream.eof())
	{
		std::getline(filestream, line);
		content.append(line + "\n");
	}
	filestream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	ShaderID = glCreateProgram();
	if (!ShaderID)
	{
		std::cerr << "failed creating a shader program !!!" << std::endl;
		return;
	}
	AddShader(ShaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(ShaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	glLinkProgram(ShaderID);

	glGetProgramiv(ShaderID, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(ShaderID, sizeof(elog), NULL, elog);
		std::cerr << "ERROR Linking program : " << elog << std::endl;
		return;
	}

	glValidateProgram(ShaderID);

	glGetProgramiv(ShaderID, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(ShaderID, sizeof(elog), NULL, elog);
		std::cerr << "ERROR Validating program : " << elog << std::endl;
		return;
	}

	uniformModel = glGetUniformLocation(ShaderID, "Model");
	uniformProjection = glGetUniformLocation(ShaderID, "Projection");
	uniformView = glGetUniformLocation(ShaderID, "View");
	uniformDirectionalLight.uniformColour = glGetUniformLocation(ShaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(ShaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(ShaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(ShaderID, "directionalLight.base.diffuseIntensity");
	uniformSpecularIntensity = glGetUniformLocation(ShaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(ShaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(ShaderID, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(ShaderID, "pointLightCount");
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuffer[100] = { '\0' };

		snprintf(locBuffer,sizeof(locBuffer),"pointLights[%d].base.colour",i);
		uniformPointLight[i].uniformColour = glGetUniformLocation(ShaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(ShaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(ShaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(ShaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant = glGetUniformLocation(ShaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformLinear = glGetUniformLocation(ShaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(ShaderID, locBuffer);
	}
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const char* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);

	glCompileShader(theShader);

	GLint result = 0;
	GLchar elog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(theShader, sizeof(elog), NULL, elog);
		std::cerr << "ERROR COMPILE program : " << shaderType << elog << std::endl;
		return;
	}

	glAttachShader(theProgram, theShader);

}


GLuint Shader::get_ProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::get_ModelLocation()
{
	return uniformModel;
}

GLuint Shader::get_ViewLocation()
{
	return uniformView;
}

GLuint Shader::get_ambientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::get_colorLocation()
{
	return uniformDirectionalLight.uniformColour;
}

GLuint Shader::get_diffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::get_directionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::get_specularIntensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::get_shininessLocation()
{
	return uniformShininess;
}

GLuint Shader::get_eyePositionLocation()
{
	return uniformEyePosition;
}

void Shader::set_DirectionalLight(DirectionalLight* dLight)
{
	dLight->useLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
					 uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::set_PointLight(PointLight* pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount, lightCount);

	for (int i = 0; i < lightCount; i++)
	{
		pLight[i].useLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour,
						   uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
						   uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
	}
}

void Shader::useShader()
{
	glUseProgram(ShaderID);
}

void Shader::ClearShader()
{
	if (ShaderID != 0)
	{
		glDeleteProgram(ShaderID);
		ShaderID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
	uniformDirectionalLight.uniformColour = 0;
	uniformDirectionalLight.uniformAmbientIntensity = 0;
	uniformDirectionalLight.uniformDirection = 0;
	uniformDirectionalLight.uniformDiffuseIntensity = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;
	uniformEyePosition = 0;

	uniformPointLightCount = 0;
}

Shader::~Shader()
{
	ClearShader();
}

