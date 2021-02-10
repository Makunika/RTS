#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // Идентификатор программы
    GLuint Program;
    // Конструктор считывает и собирает шейдер
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Использование программы
    void Use();
    // получить локейшен юниформы
    GLint GetUniformLocation(std::string uniform);

    void setFloat(std::string uniform, GLfloat value);

    void setVec4(std::string uniform, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
};

