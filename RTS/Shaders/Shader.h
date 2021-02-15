#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/fwd.hpp>

class Shader
{
public:
    GLuint Program;

    Shader(const GLchar* name);

    void use();

    GLint getUniformLocation(std::string uniform);

    void setFloat(std::string uniform, GLfloat value);

    void setVec4(std::string uniform, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);

    void setMatrix4(std::string uniform, glm::mat4& matrix);
};

