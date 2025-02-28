#pragma once

typedef unsigned int uint ;

class VertexBuffer 
{
    private:
        uint m_RendererId;
    public:
        VertexBuffer(const float* data,uint count);
        ~VertexBuffer();

        void Bind();
        void UnBind();
};

