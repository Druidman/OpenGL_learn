#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <string>
#include "Renderer.h"
#include <GL/glew.h>
#include <vector>

struct ShaderCode{
    std::string vc;
    std::string fc;
    ShaderCode(std::string vc,std::string fc): vc(vc), fc(fc){};

};

class Shader
{
    private:
        uint program;
        std::string shaderFolderPath;
        ShaderCode parseShaderFile(std::string fileName);
        void createShader(std::string vc,std::string fc);
        uint compileShader(uint shaderType, std::string shaderCode);
    public:
        Shader(std::string shaderFolderPath);
        ~Shader();
        void loadFromFile(std::string fileName);
        void bind();
        void unBind();
        void deleteShader();
        void setUniform4(std::string name,std::vector<float> params);
};
#endif