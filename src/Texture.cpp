#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(std::string path)
: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{

    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(),&m_Width,&m_Height,&m_BPP,4);
    if (!m_LocalBuffer){
        std::cerr << "IMAGE NOT LOADED";
        const char* fail = stbi_failure_reason();
        std::cout<< fail;

    }

    GlCall( glGenTextures(1,&m_RendererID) );
    GlCall( glBindTexture(GL_TEXTURE_2D,m_RendererID) );

    GlCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
    GlCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    GlCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
    GlCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

    GlCall( glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer) );
    GlCall( glBindTexture(GL_TEXTURE_2D,0) );
    if (m_LocalBuffer){
        stbi_image_free(m_LocalBuffer);
        
    }

}

Texture::~Texture()
{
    GlCall(glDeleteTextures(1,&m_RendererID));
}

void Texture::Bind(uint slot)
{
    GlCall( glActiveTexture(GL_TEXTURE0 + slot) );
    GlCall( glBindTextureUnit(slot,m_RendererID) );
}

void Texture::UnBind()
{
    GlCall( glBindTexture(GL_TEXTURE_2D,0) );
}
