#include "VertexBufferLayout.h"

uint VertexBufferLayout::count()
{
    return layout.size();
}

void VertexBufferLayout::setAttrib(uint index, uint count, uint type)
{
    VertexAttributeElement element(index,count,type);
    layout.push_back(element);
}

uint VertexBufferLayout::getStride()
{
    uint stride=0;
    for (int i =0; i<layout.size();i++){
        stride += layout[i].count * layout[i].getSizeOfType();
    }
    return stride;
}
