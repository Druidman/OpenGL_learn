#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "tests/testClearColor.h"
#include "tests/testTexture2D.h"
#include "tests/testVertexColor.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <fstream>
#include <string>
#include "Texture.h"

enum ActiveTest{
    ClearColor,
    Texture2D,
    VertexColor,
    None
};

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
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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
         50.0,  50.0,    1.0, 0.0, 0.0, 1.0,  0.0,    0.0,0.0,
         50.0, 100.0,    1.0, 0.0, 0.0, 1.0,  0.0,    0.0,1.0,
        100.0,  50.0,    1.0, 0.0, 0.0, 1.0,  0.0,    1.0,0.0,
        100.0, 100.0,    1.0, 0.0, 0.0, 1.0,  0.0,    1.0,1.0,


        150.0,  50.0,    1.0, 0.0, 0.0, 1.0,  1.0,    0.0,0.0,
        150.0, 100.0,    1.0, 0.0, 0.0, 1.0,  1.0,    0.0,1.0,
        200.0,  50.0,    1.0, 0.0, 0.0, 1.0,  1.0,    1.0,0.0,
        200.0, 100.0,    1.0, 0.0, 0.0, 1.0,  1.0,    1.0,1.0
    };

    uint indices[] = {
        0,1,2,
        2,3,1,

        4,5,6,
        6,7,5

    };

    GlCall( glEnable(GL_BLEND) );
    GlCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
 

    VertexArray vao;
    vao.bind();

    VertexBuffer vb = VertexBuffer(positions,std::size(positions));
    VertexBufferLayout layout;
    layout.setAttrib(0,2,GL_FLOAT);
    layout.setAttrib(1,4,GL_FLOAT);
    layout.setAttrib(2,1,GL_FLOAT);
    layout.setAttrib(3,2,GL_FLOAT);

    vao.addVertexBuffer(&vb,&layout);

    IndexBuffer ib = IndexBuffer(indices,std::size(indices));

    glm::mat4 proj = glm::ortho(0.0, 960.0, 0.0, 540.0,-1.0,1.0);
    glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(0,0,0));



    Shader shader = Shader("../res/shaders/");
    shader.loadFromFile("Basic.shader");
    shader.bind();
 

    vao.unBind();
    shader.unBind();
    vb.UnBind();
    ib.UnBind();

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    
    ImGui::StyleColorsDark();

    Renderer renderer;

    ActiveTest activeTest = None;
    test::ClearColor clearColorTest;
    test::Texture2D texture2DTest(shader,proj,view,renderer,vao,ib);
    test::VertexColor vertexColorTest(shader,proj,view,renderer,vao,ib);
    
    while (!glfwWindowShouldClose(window))  
    {
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       
        shader.bind();
    
        {
              
            switch (activeTest){
                case ClearColor:
                    clearColorTest.onRender();
                    if (!clearColorTest.onImGuiRender()){
                        clearColorTest.~ClearColor();
                        activeTest = None;
                    };
                    break;
                case Texture2D:
                    texture2DTest.onRender();
                    if (!texture2DTest.onImGuiRender()){
                        texture2DTest.~Texture2D();
                        activeTest = None;
                    };
                    break;
                case VertexColor:
                    vertexColorTest.onRender();
                    if (!vertexColorTest.onImGuiRender()){
                        vertexColorTest.~VertexColor();
                        activeTest = None;
                    };
                    break;
                
                case None:
                    ImGui::Begin("Test Menu");
                    if (ImGui::Button("ClearColor",ImVec2(200,25))){
                        activeTest = ClearColor;
                    }
                    if (ImGui::Button("2D texture",ImVec2(200,25))){
                        activeTest = Texture2D;
                    }  
                    if (ImGui::Button("Vertex Color",ImVec2(200,25))){
                        activeTest = VertexColor;
                    }  
                    ImGui::Text("FPS: %f",ImGui::GetIO().Framerate);
                        
                    ImGui::End();
                    break;
            }
           
            

            
            
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
    }
    shader.deleteShader();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    

    glfwTerminate();
    return 0;
}
