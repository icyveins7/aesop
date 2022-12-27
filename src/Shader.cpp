#include "Shader.h"
#include <iostream>
#include <cstring>

Shader::Shader(const char *vertexCode, const char *fragmentCode) {
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Error creating shaderID program\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// error checking
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	// 'binds' uniformXMove in program to "xMove" in shaderID program
	// uniformModel = glGetUniformLocation(shaderID, "model");

	// uniformProjection = glGetUniformLocation(shaderID, "projection");

	// uniformView = glGetUniformLocation(shaderID, "view");

	uniformVp = glGetUniformLocation(shaderID, "vp");
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	// note, use 'theShader' for all calls here, not the global 'shader' !!

	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::UseShader() {
	glUseProgram(shaderID);
}

void Shader::ClearShader() {
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	// uniformModel = 0;
	// uniformProjection = 0;
	// uniformView = 0;
}


Shader::~Shader() {
	ClearShader();
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream filestream(fileLocation, std::ios::in);

	if (!filestream.is_open()) {
		printf("Failed to read %s, file doesn't exist.\n", fileLocation);
		throw 1;
	}

	std::string line = "";
	while (!filestream.eof()) {
		std::getline(filestream, line);
		content.append(line + "\n");
	}

	filestream.close();
	return content;
}

// =============================
PlotShader::PlotShader()
	: Shader{
		Shader::ReadFile("../shaders/PlotShader.vert").c_str(),
		Shader::ReadFile("../shaders/PlotShader.frag").c_str()
	}
{
    
}

PlotShader::~PlotShader()
{

}