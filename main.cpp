#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int params;
    glGetShaderiv(id,GL_COMPILE_STATUS,&params);

    if (params == GL_FALSE){
        int logMsgLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH,&logMsgLength);

        char *msg = (char*)alloca(logMsgLength * sizeof(char));
        glGetShaderInfoLog(id,logMsgLength,&logMsgLength,msg);
        std::cout << "Failed to compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
        std::cout << msg << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;

}

int main(void)
{
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

    if (glewInit() != GLEW_OK){
        std::cout << "glew init failed" << "\n";
    }
    std::cout << glGetString(GL_VERSION) << "\n";
    float positions[6] = {
        -0.5, -0.5,
         0.0,  0.5,
         0.5, -0.5
    };

    
    
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);

   
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);
    
    ShaderCode source = ParseShader("res/shaders/Basic.shader");
    std::cout << source.vertexCode;
    unsigned int shader = createShader(source.vertexCode, source.fragmentCode);
    glUseProgram(shader);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES,0,3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}