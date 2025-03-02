#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>

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

    VertexArray vao;
    vao.bind();

    VertexBuffer vb = VertexBuffer(positions,std::size(positions));
    VertexBufferLayout layout;
    layout.setAttrib(0,2,GL_FLOAT);

    vao.addVertexBuffer(&vb,&layout);

    IndexBuffer ib = IndexBuffer(indices,std::size(indices));


    Shader shader = Shader("../res/shaders/");
    shader.loadFromFile("Basic.shader");
    shader.bind();


    vao.unBind();
    shader.unBind();
    vb.UnBind();
    ib.UnBind();

    Renderer renderer;
    
    float increment = 0.05;
    std::vector<float> colors = {0.0, 0.3, 0.5, 1.0};
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))  
    {
        renderer.Clear();
        shader.bind();
        shader.setUniform4("u_Color",colors);
        
       
        renderer.Draw(vao,ib,shader);


        if (colors[0] > 1.0){
            increment = -0.05;
        }
        else if (colors[0] < 0.0){
            increment = 0.05;
        }

        colors[0] += increment;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    shader.deleteShader();
    

    glfwTerminate();
    return 0;
}
