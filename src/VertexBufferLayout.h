#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H
typedef unsigned int uint;
#include <vector>
#include <GL/glew.h>
#include <iostream>

struct VertexAttributeElement{
    uint index;
    uint count;
    uint type;

    VertexAttributeElement(uint index,uint count,uint type) : index(index), count(count), type(type){};
   

    uint getSizeOfType(){
        uint byteSize;
        switch (type){
            case GL_FLOAT:
                byteSize = sizeof(float);
                break;
            case GL_INT:
                byteSize = sizeof(int);
                break;
            case GL_DOUBLE:
                byteSize = sizeof(double);
                break;
            case GL_UNSIGNED_INT:
                byteSize = sizeof(uint);
                break;
            default:
                byteSize = sizeof(float);
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
        uint getStride();
        
        inline std::vector<VertexAttributeElement> getLayout(){ return layout; }

};
#endif
