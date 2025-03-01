#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H
typedef unsigned int uint;
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"
#include <iostream>

struct VertexAttributeElement{
    uint index;
    uint count;
    uint type;

    VertexAttributeElement(uint index,uint count,uint type) : index(index), count(count), type(type){};
   

    uint getStride(){
        uint byteSize;
        switch (type){
            case GL_FLOAT:
                byteSize = sizeof(float) * count;
                break;
            case GL_INT:
                byteSize = sizeof(int) * count;
                break;
            case GL_DOUBLE:
                byteSize = sizeof(double) * count;
                break;
            case GL_UNSIGNED_INT:
                byteSize = sizeof(uint) * count;
                break;
            default:
                byteSize = sizeof(float) * count;
                break;
            
        }
        
        return byteSize;
    }
};

class VertexBufferLayout
{
    private: 
        std::vector<VertexAttributeElement> layout;
    public: 
        
        uint count();

        void setAttrib(uint index, uint count, uint type);

        
        inline std::vector<VertexAttributeElement> getLayout(){ return layout; }

};
#endif
