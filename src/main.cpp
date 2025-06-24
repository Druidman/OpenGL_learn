#include <iostream>
#include "vendor/stb_image/stb_image.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
float fov = 45.0;

float mixVal = 0.5;
glm::vec2 mousePos = glm::vec2(0.0,0.0);
float cameraYaw = 0;
float cameraPitch = 0;
glm::vec3 cameraPos = glm::vec3(0,0,3);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

glm::vec3 cameraUp = glm::vec3(0.0,1.0,0.0);
bool firstMouse = true;


void processInput(GLFWwindow* window){
    const float cameraSpeed = 0.05;
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
    else if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS){
        mixVal += 0.01;
    }
    else if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS){
        mixVal -= 0.01;
    }

    else if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed * cameraFront;
    }
    else if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront));
    }
    else if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * cameraFront;
    }
    else if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront));
    }
}

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"


    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"

    "out vec2 TexCoord;\n"

    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model *  vec4(aPos, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
    "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"uniform float mixVal;\n"

"void main()\n"
"{\n"
"   FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.x,TexCoord.y)), mixVal);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    
    glViewport(0,0,width,height);
    WINDOW_HEIGHT = height;
    WINDOW_WIDTH = width;
}
void cursorPosCallback(GLFWwindow *window, double xpos, double ypos){
    if (firstMouse){
        mousePos.x = xpos;
        mousePos.y = ypos;
        firstMouse = false;
    }
    double changex = xpos - mousePos.x;
    double changey = mousePos.y - ypos;
    mousePos = glm::vec2(xpos,ypos);

    cameraYaw += 180 * (changex / WINDOW_WIDTH);
    cameraPitch += 180 * (changey / WINDOW_HEIGHT);

    glm::vec3 direction;
    direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    direction.y = sin(glm::radians(cameraPitch));
    direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    

    cameraFront = glm::normalize(direction);

    

    
}
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset){
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 90.0f)
        fov = 90.0f; 

    
}
int main(){
    
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    


    stbi_set_flip_vertically_on_load(true);  

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   
    glfwSetCursorPosCallback(window,cursorPosCallback);

    glfwSetScrollCallback(window, scrollCallback);


    glm::mat4 model = glm::mat4(1.0);
    model = glm::rotate(model,(float)glm::radians(-60.0),glm::vec3(1.0,0.0,0.0));

    glm::mat4 view;
    

    glm::mat4 projection;
    
    projection = glm::perspective(glm::radians((double)fov),(double)1920/1080,0.1,100.0);
    

    glViewport(0,0,1920,1080);
    uint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);


    uint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1,&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    uint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };
    

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 3,   // first triangle
    //     1, 2, 3    // second triangle
    // }; 
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)
    }; 

    int width1, height1, nrChannels1;
    unsigned char *data1 = stbi_load("wall.jpg",&width1,&height1,&nrChannels1,0);

    int width2, height2, nrChannels2;
    unsigned char *data2 = stbi_load("awesomeface.png",&width2,&height2,&nrChannels2,0);

    uint texture1, texture2;
    glGenTextures(1,&texture1);
    glGenTextures(1,&texture2);

    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);


    glBindTexture(GL_TEXTURE_2D,texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);

    uint VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    uint VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // uint EBO;
    // glGenBuffers(1,&EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 



    
    
    glEnable(GL_DEPTH_TEST);  
    while (!glfwWindowShouldClose(window)){
        int w = WINDOW_WIDTH;
        int h = WINDOW_HEIGHT;
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        glUniform1i(glGetUniformLocation(shaderProgram,"texture1"),0);
        glUniform1i(glGetUniformLocation(shaderProgram,"texture2"),1);

        glUniform1f(glGetUniformLocation(shaderProgram,"mixVal"),mixVal);
        
    
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians((double)fov),(double)1920/1080,0.1,100.0);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);  
        glBindVertexArray(VAO);
        for (int i =0; i < std::size(cubePositions); i++){
            glm::mat4 model = glm::mat4(1.0);
            model = glm::translate(model,cubePositions[i]);
            float angle = 20.0 * i;
            
            model = glm::rotate(model,(float)glfwGetTime() * glm::radians(angle),glm::vec3(1.0,0.3,0.5));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);


        }

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        
        
        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    
    glfwTerminate();

    return 0;
}