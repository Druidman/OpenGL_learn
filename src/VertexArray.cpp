#include "VertexArray.h"
#include "Renderer.h"
#include <GL/glew.h>
#include <iostream>

VertexArray::VertexArray()
{
    GlCall( glGenVertexArrays(1,&m_vao) );
}

VertexArray::~VertexArray()
{
    unBind();
}

void VertexArray::bind()
{
    GlCall( glBindVertexArray(m_vao) );
}

void VertexArray::unBind()
{
    GlCall( glBindVertexArray(0) );
}

void VertexArray::addVertexBuffer(VertexBuffer* vbo, VertexBufferLayout* layout)
{
    
    (*vbo).Bind();

    std::vector<VertexAttributeElement> elements = (*layout).getLayout();
    for (int i = 0;i<elements.size();i++){

        VertexAttributeElement element = elements[i];

        GlCall( glEnableVertexAttribArray(element.index) );

        GlCall( glVertexAttribPointer(
            element.index,
            element.count,
            element.type,
            GL_FALSE,
            element.getStride(),
            0
        ) );
    }
}