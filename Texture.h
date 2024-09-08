#pragma once

#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
private:
	GLuint TextureID;
	int width, height, bitDepth;

	char* fileLocation;
public:
	Texture();
	Texture(char* fileLoc);

	void loadTexture();
	void useTexture();
	void clearTexture();

	~Texture();

};

