#pragma once
#include <GL/glew.h>


class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	virtual void RenderMesh() = 0;
	void ClearMesh();

	~Mesh();

protected:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

class LineMesh : public Mesh
{
public:
    LineMesh();
    ~LineMesh();

    virtual void RenderMesh() override;

}