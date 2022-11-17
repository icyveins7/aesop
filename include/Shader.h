#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>

// Helper function for loading shaders from files
std::string ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream filestream(fileLocation, std::ios::in);

	if (!filestream.is_open()) {
		printf("Failed to read %s, file doesn't exist.\n", fileLocation);
		return "";
	}

	std::string line = "";
	while (!filestream.eof()) {
		std::getline(filestream, line);
		content.append(line + "\n");
	}

	filestream.close();
	return content;
}

/* The parent shader class */
class Shader
{
public:
	Shader(const char *vertexCode, const char *fragmentCode);
	~Shader();

    void UseShader();
    void ClearShader();

    // Getters
    // inline GLuint GetProjectionLocation() {
    //     return uniformProjection;
    // }

    // inline GLuint GetModelLocation() {
    //     return uniformModel;
    // }

    inline GLuint GetViewLocation() {
        return uniformView;
    }


protected:
	GLuint shaderID = 0;
    // GLuint uniformProjection = 0;
    // GLuint uniformModel = 0;
    GLuint uniformView = 0;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

// ==============================================
class LineItemShader : public Shader
{
public:
    LineItemShader();
    ~LineItemShader();
};
