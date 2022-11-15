#pragma once
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char *vertexCode, const char *fragmentCode);
	~Shader();

    void UseShader();
    void ClearShader();

    // Getters
    inline GLuint Shader::GetProjectionLocation() {
        return uniformProjection;
    }

    inline GLuint Shader::GetModelLocation() {
        return uniformModel;
    }

    inline GLuint Shader::GetViewLocation() {
        return uniformView;
    }

protected:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

// ==============================================
class LineItemShader : public Shader
{
public:
    LineItemShader(const char *vertexCode, const char *fragmentCode);
    ~LineItemShader();
};
