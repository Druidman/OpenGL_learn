#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <vector>
#include <iostream>

ShaderCode Shader::parseShaderFile(std::string fileName)
{
    std::ifstream stream(shaderFolderPath + fileName);
    enum ReadMode{
        NONE = -1, VERTEX=0, FRAGMENT=1
    };

    std::string line;

    std::string vc;
    std::string fc;

    ReadMode readMode = NONE;

    while (getline(stream,line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                readMode = VERTEX;
            }
            else if (line.find("fragment") != std::string::npos){
                readMode = FRAGMENT;
            }
        }
        else {
            switch (readMode){
                case NONE:
                    break;
                case VERTEX:
                    vc += line + "\n";
                    break;
                case FRAGMENT:
                    fc += line + "\n";
                    break;
            }
        }
    }

    return ShaderCode(vc,fc);
}

void Shader::createShader(std::string vc, std::string fc)
{
    uint vs = compileShader(GL_VERTEX_SHADER, vc);
    uint fs = compileShader(GL_FRAGMENT_SHADER, fc);

    GlCall( glAttachShader(program,vs) );
    GlCall( glAttachShader(program,fs) );

    GlCall( glLinkProgram(program) );
    GlCall( glValidateProgram(program) );

    GlCall( glDeleteShader(vs) );
    GlCall( glDeleteShader(fs) );
}

uint Shader::compileShader(uint shaderType, std::string shaderCode)
{
    unsigned int id = glCreateShader(shaderType);
    const char* src = &shaderCode[0];
    GlCall( glShaderSource(id,1,&src,nullptr) );
    GlCall( glCompileShader(id) );

    int params;
    GlCall( glGetShaderiv(id,GL_COMPILE_STATUS,&params) );

    if (params == GL_FALSE){
        int logMsgLength;
        GlCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH,&logMsgLength) );

        char *msg = (char*)alloca(logMsgLength * sizeof(char));
        GlCall( glGetShaderInfoLog(id,logMsgLength,&logMsgLength,msg) );
        std::cout << "Failed to compile shader" << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
        std::cout << msg << "\n";
        GlCall( glDeleteShader(id) );
        return 0;
    }
    return id;
}

Shader::Shader(std::string shaderFolderPath)
: shaderFolderPath(shaderFolderPath)
{
    program = glCreateProgram();
}

Shader::~Shader()
{
}

void Shader::loadFromFile(std::string fileName)
{
    ShaderCode sources = parseShaderFile(fileName);
    createShader(sources.vc,sources.fc);


}

void Shader::bind()
{
    GlCall( glUseProgram(program) );

}

void Shader::unBind()
{
    GlCall( glUseProgram(0) );
}

void Shader::deleteShader()
{
    GlCall( glDeleteProgram(program) );
}

void Shader::setUniform4f(std::string name, std::vector<float> params)
{
    GlCall( glUniform4f(getUniformLocation(name),params[0],params[1],params[2],params[3]) )
}

void Shader::setUniformMat4f(std::string name, glm::mat4 &matrix)
{
    GlCall( glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,&matrix[0][0]) )
}

void Shader::setUniform1i(std::string name, int param)
{
   
    GlCall( glUniform1i(getUniformLocation(name),param) )

}


int Shader::getUniformLocation(std::string name){
    if (uniformLocationCache.find(name) == uniformLocationCache.end()){
        int location = glGetUniformLocation(program,name.c_str());
        ASSERT(location != -1);
        uniformLocationCache[name] = location;
        return location;
    }
    return uniformLocationCache[name];
    
}