#include "VertexBuffer.h"
#include <GL/glew.h>
#include "Renderer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const float* data,uint count)
{
    GlCall( glGenBuffers(1,&m_RendererId) );
    GlCall( glBindBuffer(GL_ARRAY_BUFFER,m_RendererId) );
    GlCall( glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, GL_STATIC_DRAW) );
}

VertexBuffer::~VertexBuffer()
{
    GlCall( glDeleteBuffers(1,&m_RendererId) );
}

void VertexBuffer::Bind()
{
    GlCall( glBindBuffer(GL_ARRAY_BUFFER,m_RendererId) );
}

void VertexBuffer::UnBind()
{
    GlCall( glBindBuffer(GL_ARRAY_BUFFER,0) );
}
