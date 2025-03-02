#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) exit(0);
#define GlCall(x) GlClearError();\
    x;\
    ASSERT(GlCheckError(#x, __FILE__, __LINE__));

void GlClearError();
bool GlCheckError(const char* function,const char* file, int line);


class Renderer
{
    private:
    public:
        void Draw(VertexArray& va,IndexBuffer& ib,Shader& shader);
        void Clear();
};



    
#endif