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

