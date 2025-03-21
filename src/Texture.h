#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer.h"
typedef unsigned int uint;



class Texture
{
private:
    uint m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(std::string path);
    ~Texture();

    void Bind(uint slot=0);
    void UnBind();

    inline int getWidth() const {return m_Width;};
    inline int getHeight() const {return m_Height;};
    inline uint getId() const {return m_RendererID;};
};   
#endif
