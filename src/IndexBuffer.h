#pragma once

typedef unsigned int uint ;

class IndexBuffer 
{
    private:
        uint m_RendererId;
        uint m_Count;
    public:
        IndexBuffer(const uint data[],uint count);
        ~IndexBuffer();

        void Bind();
        void UnBind();
        
        inline uint GetCount() { return m_Count; };
};