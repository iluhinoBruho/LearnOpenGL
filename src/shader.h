#ifndef SHADER_H
#define SHADER_H

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


char* readShader(const char* filename){
    char* buffer = 0;
    long length;
    FILE* f = fopen (filename, "rb");
    
    if(f){
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
        return buffer;
    }else{
        printf("error while reading file");
    }   
}


struct Shader{
    GLchar* fragmentShaderSource;
    GLchar* vertexShaderSource;

    GLuint Program;
};


void initShader(struct Shader *s, const char* vertexPath, const char* fragmentPath){
    s->fragmentShaderSource = NULL;
    s->vertexShaderSource = NULL;
    //(*s).fragmentShaderSource = readShader(vertexPath);
    s->vertexShaderSource = readShader(vertexPath);
    s->fragmentShaderSource = readShader(fragmentPath);

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &s->vertexShaderSource, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        printf(infoLog);
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &s->fragmentShaderSource, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
        printf(infoLog);
    };

    s->Program = glCreateProgram();

    glAttachShader(s->Program, vertex);
    glAttachShader(s->Program, fragment);
    glLinkProgram(s->Program);

    glGetProgramiv(s->Program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(s->Program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
        printf(infoLog);
    }

    //Deleting shaders, cause we've wrote them into programm
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void UseShader(struct Shader *s){
    glUseProgram(s->Program);
}



#endif
