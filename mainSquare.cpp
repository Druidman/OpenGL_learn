#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

uint compileShader(string &shaderSource, uint type){
    uint shader = glCreateShader(type);
    const char *src = &shaderSource[0];
    glShaderSource(shader,1, &src,nullptr);
    glCompileShader(shader);

    int params;
    glGetShaderiv(shader, GL_COMPILE_STATUS,&params);
    if (params == GL_FALSE){
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH,&length);
        char *infoLog = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader,length,&length,infoLog);
        cout << "Error occured in compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << "\n";
        cout << infoLog << "\n";
        glDeleteShader(shader);
        return 0;
    }


    return shader;

}

uint CreateShader(string &vertexSource, string &fragmentSource){
    uint program = glCreateProgram();

    uint vs = compileShader(vertexSource, GL_VERTEX_SHADER);
    uint fs = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    glAttachShader(program,vs);
    glAttachShader(program,fs);

    glLinkProgram(program);
    glValidateProgram(program);

    
    return program;

}

int main(){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    unsigned int err = glewInit();
    if (err != GLEW_OK){
        cout << "ERROR INITING GLEW\n" << glewGetErrorString(err) << "\n";
    }

    float positions[8] = {
        -0.5, -0.5,
        -0.5,  0.5,
         0.5, -0.5,
         0.5,  0.5
    };
    uint indicies[] = {
        0,1,2,
        1,3,2
    };
    uint posBuffer;
    glCreateBuffers(1,&posBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,posBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);

    uint indBuffer;
    glCreateBuffers(1,&indBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indicies),indicies,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    string vertexShader = 
        "#version 330 core\n"
        "layout(location =0 ) in vec4 vertex_position;\n"
        "\n"
        "void main(){\n"
        "   gl_Position = vertex_position;\n"
        "}\n"
        
        ;
    string fragmentShader = 
        "#version 330 core\n"
        "layout(location =0 ) out vec4 color;\n"
        "\n"
        "void main(){\n"
        "   color = vec4(1.0,0.0,0.0,1.0);\n"
        "}\n"
        
        ;

  
    uint shader = CreateShader(vertexShader,fragmentShader);
    glUseProgram(shader);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_POINTS,6,GL_UNSIGNED_INT,0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}