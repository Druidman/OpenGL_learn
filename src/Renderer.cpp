#include "Renderer.h"
#include <iostream>

void GlClearError(){
    while (glGetError());
}

bool GlCheckError(const char* function,const char* file, int line){
    while (uint error = glGetError()){
        std::cout << "OPENGL ERROR \n" << error << "\n" << function << " " << file << " " << "LINE " << line << "\n";
        return false;
    }
    return true;
}