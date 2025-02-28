#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <iostream>
#include <fstream>

#include <string>

struct ShaderCode {
    std::string vertexCode;
    std::string fragmentCode;
};

ShaderCode ParseShader(const std::string &filepath){
    std::ifstream stream(filepath);


    enum ReadMode{
        NONE = -1, VERTEX=0, FRAGMENT=1
    };


    std::string line;

    std::string vertexShader;
    std::string fragmentShader;

    ReadMode readMode = NONE;

    while (getline(stream,line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                readMode = VERTEX;
            }
            else if (line.find("fragment") != std::string::npos){
                readMode = FRAGMENT;
            }
        }
        else {
            switch (readMode){
                case NONE:
                    break;
                case VERTEX:
                    vertexShader += line + "\n";
                    
                    break;
                case FRAGMENT:
                    fragmentShader += line + "\n";
                    break;
            }
        }
    }
    return { 
        vertexShader,
        fragmentShader 
    };
}

int compileShader(unsigned int type, const std::string& shader)
{
    unsigned int id = glCreateShader(type);
    const char* src = &shader[0];
    GlCall( glShaderSource(id,1,&src,nullptr) );
    GlCall( glCompileShader(id) );

    int params;
    GlCall( glGetShaderiv(id,GL_COMPILE_STATUS,&params) );

    if (params == GL_FALSE){
        int logMsgLength;
        GlCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH,&logMsgLength) );

        char *msg = (char*)alloca(logMsgLength * sizeof(char));
        GlCall( glGetShaderInfoLog(id,logMsgLength,&logMsgLength,msg) );
        std::cout << "Failed to compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
        std::cout << msg << "\n";
        GlCall( glDeleteShader(id) );
        return 0;
    }
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GlCall( glAttachShader(program,vs) );
    GlCall( glAttachShader(program,fs) );

    GlCall( glLinkProgram(program) );
    GlCall( glValidateProgram(program) );

    GlCall( glDeleteShader(vs) );
    GlCall( glDeleteShader(fs) );
    
    return program;

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK){
        std::cout << "glew init failed" << "\n";
    }
    std::cout << glGetString(GL_VERSION) << "\n";

    float positions[] = {
        -0.5, -0.5,
        -0.5,  0.5,
         0.5,  0.5,
         0.5, -0.5
    };

    uint indices[] = {
        0,1,2,
        0,3,2

    };
    

    uint vao;
    GlCall( glGenVertexArrays(1,&vao) );
    GlCall( glBindVertexArray(vao) );


    VertexBuffer vb = VertexBuffer(positions,std::size(positions));
    GlCall( glEnableVertexAttribArray(0) );
    GlCall( glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),0) );

    IndexBuffer ib = IndexBuffer(indices,std::size(indices));

    
    ShaderCode source = ParseShader("../res/shaders/Basic.shader");
    uint shader = createShader(source.vertexCode, source.fragmentCode);

    GlCall( glUseProgram(shader) );

    int location = glGetUniformLocation(shader,"u_Color");
    ASSERT(location != -1);

    GlCall( glBindVertexArray(0) );
    GlCall( glUseProgram(0) );
    GlCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    GlCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0) );

    float r = 0.0;
    float g = 0.3;
    float b = 0.5;
    float increment = 0.05;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))  
    {
        /* Render here */
        GlCall( glClear(GL_COLOR_BUFFER_BIT) ); 

        GlCall( glUseProgram(shader) );
        GlCall( glUniform4f(location,r,g,b,1.0) );

        GlCall( glBindVertexArray(vao) );
    
       
        GlCall( glDrawElements(GL_TRIANGLES,std::size(indices),GL_UNSIGNED_INT,nullptr) );

        if (r > 1.0){
            increment = -0.05;
        }
        else if (r < 0.0){
            increment = 0.05;
        }

        r += increment;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    GlCall( glDeleteProgram(shader) );

    glfwTerminate();
    return 0;
}
