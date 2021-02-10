#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // ������������� ���������
    GLuint Program;
    // ����������� ��������� � �������� ������
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // ������������� ���������
    void Use();
    // �������� �������� ��������
    GLint GetUniformLocation(std::string uniform);

    void setFloat(std::string uniform, GLfloat value);

    void setVec4(std::string uniform, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
};

