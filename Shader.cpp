#include "Shader.h"


Shader::Shader()
{
	ShaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
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
}

Shader::~Shader()
{
	ClearShader();
}

