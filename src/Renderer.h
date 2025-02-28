#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) exit(0);
#define GlCall(x) GlClearError();\
    x;\
    ASSERT(GlCheckError(#x, __FILE__, __LINE__));

void GlClearError();
bool GlCheckError(const char* function,const char* file, int line);
    
