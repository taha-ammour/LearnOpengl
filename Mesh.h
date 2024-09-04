#pragma once

#include <GL/glew.h>


class Mesh
{
public:
	Mesh();

	void Create_Mesh(GLfloat* verticies, unsigned int *indicies, unsigned int num_of_verticies, unsigned int num_of_indices);
	void Render_Mesh();
	void Clear_Mesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

};

