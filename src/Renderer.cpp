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

void Renderer::Draw(VertexArray &va, IndexBuffer &ib, Shader &shader)
{
    shader.bind();
    va.bind();
    ib.Bind();

    GlCall( glDrawElements(GL_TRIANGLES,ib.GetCount(),GL_UNSIGNED_INT,nullptr) );
}

void Renderer::Clear()
{
    GlCall( glClear(GL_COLOR_BUFFER_BIT) ); 
}
