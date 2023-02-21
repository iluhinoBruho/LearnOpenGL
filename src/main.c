#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// // Shaders
// const GLchar* vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 position;\n"
//     "layout (location = 1) in vec3 color;\n"
//     "out vec3 ourColor;\n"
//     "void main()\n"
//     "{\n"
//     "gl_Position = vec4(position, 1.0);\n"
//     "ourColor = color;\n"
//     "}\0";
// const GLchar* fragmentShaderSource = "#version 330 core\n"
//     "out vec4 color;\n"
//     "uniform vec4 ourColor;\n"
//     "void main()\n"
//     "{\n"
//     "color = ourColor;\n"
//     "}\n\0";


char* readShader(const char* filename){
    char* buffer = 0;
    long length;
    FILE* f = fopen (filename, "rb");

    if (f){
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer){
            fread (buffer, 1, length, f);
        }
        fclose (f);
    } else{
        printf("error while opening file");
    }

    if (buffer){
        // char* ret = buffer;
        // while(*buffer!='\0'){
        //     printf("%c",*buffer++);
            
        // }
        // printf("CHEECK->%c<-",*ret);
        // return ret;
        return buffer;
    }else{
        printf("error while reading file");
    }
    
}
//     char* buffer = 0;
//     long length;
//     FILE* f = fopen(filename, "rb");

//     if (f){
//         fseek (f, 0, SEEK_END);
//         length = ftell (f);
//         fseek (f, 0, SEEK_SET);
//         buffer = malloc (length);
//         if (buffer)
//         {
//             fread (buffer, 1, length, f);
//         }
//         fclose (f);
//     }else{
//         printf("error opening file");
//     }
//     if(buffer){
//         printf(*buffer);
//         return buffer;
//     }else{
//         printf("error reading file");
//     }
// }

struct Shader{
    GLchar* fragmentShaderSource;
    GLchar* vertexShaderSource;
};


void initShader(struct Shader *s, const char* vertexPath, const char* fragmentPath){
    s->fragmentShaderSource = NULL;
    s->vertexShaderSource = NULL;
    //(*s).fragmentShaderSource = readShader(vertexPath);
    s->vertexShaderSource = readShader(vertexPath);
    s->fragmentShaderSource = readShader(fragmentPath);

}

// void UseShader(struct Shader s){

// }

int main(){
    struct Shader test;
    //initShader(&test, "./shaders/default.vs", "./shaders/default.fs");
    initShader(&test, "/home/ilya/OpenGL/Lesson3/shaders/default.vs", "/home/ilya/OpenGL/Lesson3/shaders/default.fs");
    printf(test.vertexShaderSource);
    printf(test.fragmentShaderSource);
    return 0;
}
/*
// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);


    // Build and compile our shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        //std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        //std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        //std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions        
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
         0.0f,  0.5f, 0.0f   // Top 
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Be sure to activate the shader
        glUseProgram(shaderProgram);

        // Update the uniform color
        GLfloat timeValue = glfwGetTime();
        double tmp = sin( timeValue );
        GLfloat greenValue = (tmp / 2) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

*/