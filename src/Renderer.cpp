#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

void GlClearError(){
    while (glGetError());
}

bool GlCheckError(const char* function,const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout << "OPENGL ERROR \n" << error << "\n" << function << " " << file << " " << "LINE " << line << "\n";
        return false;
    }
    return true;
}