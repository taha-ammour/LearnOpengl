#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
private:
	GLuint ShaderID, uniformModel, uniformProjection, uniformView, uniformAmbientIntensity, uniformAmbientColour;
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
	GLuint get_ambientColorLocation();


	void useShader();
	void ClearShader();

	~Shader();
};

