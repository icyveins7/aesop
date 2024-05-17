#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>

/* The parent shader class */
class Shader
{
public:
    Shader(const char *vertexCode, const char *fragmentCode, const char *geometryCode = nullptr);
    ~Shader();

    // Helper function for loading shaders from files
    static std::string ReadFile(const char* fileLocation);

    void UseShader();
    void ClearShader();

    // Getters
    // inline GLuint GetProjectionLocation() {
    //     return uniformProjection;
    // }

    // inline GLuint GetModelLocation() {
    //     return uniformModel;
    // }

    // inline GLuint GetViewLocation() {
    //     return uniformView;
    // }

    inline GLuint GetVpLocation(){return uniformVp;}
    inline GLfloat GetHalfLengthLocation(){ return uniformHalflength; } // TODO: move to classes that actually always need this
    inline GLuint GetShaderID(){ return shaderID; }

protected:
    GLuint shaderID = 0;
    // GLuint uniformProjection = 0;
    // GLuint uniformModel = 0;
    // GLuint uniformView = 0;

    // Combined the matrices
    GLuint uniformVp = 0;
    GLfloat uniformHalflength = 0.0f; // TODO: move this to classes that actually need this

    void CompileShader(const char* vertexCode, const char* fragmentCode, const char* geometryCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

// ==============================================
class PlotShader : public Shader
{
public:
    PlotShader();
    ~PlotShader();
};

// ==============================================
class HeatmapShader : public Shader
{
public:
    HeatmapShader();
    ~HeatmapShader();
};
