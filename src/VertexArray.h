#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
    private:
    uint m_vao;
    public:
        
        VertexArray();
        ~VertexArray();
        void bind();
        void unBind();

        void addVertexBuffer(VertexBuffer* vbo, VertexBufferLayout* layout);
        


};

#endif