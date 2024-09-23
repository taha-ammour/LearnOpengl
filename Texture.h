#pragma once

#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
private:
	GLuint TextureID;
	int width, height, bitDepth;

	const char* fileLocation;
public:
	Texture();
	Texture(const char* fileLoc);

	bool loadTexture();
	bool loadTextureA();
	void useTexture();
	void clearTexture();

	~Texture();

};

