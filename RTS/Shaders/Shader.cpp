#include "Shader.h"
#include "../Utils.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const GLchar* name)
{
    // 1. Получаем исходный код шейдера из filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // Удостоверимся, что ifstream объекты могут выкидывать исключения
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vShaderFile.open(Utils::getShaderPathString(std::string(name) + ".vert"));
        fShaderFile.open(Utils::getShaderPathString(std::string(name) + ".frag"));
        std::stringstream vShaderStream, fShaderStream;
        // Считываем данные в потоки
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();
        // Преобразовываем потоки в массив GLchar
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // 2. Сборка шейдеров
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Если есть ошибки - вывести их
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Шейдерная программа
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    //Если есть ошибки - вывести их
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Удаляем шейдеры, поскольку они уже в программу и нам больше не нужны.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(this->Program);
}

GLint Shader::getUniformLocation(std::string uniform)
{
    return glGetUniformLocation(this->Program, uniform.c_str());
}

void Shader::setFloat(std::string uniform, GLfloat value)
{
    GLint vertexColorLocation = this->getUniformLocation(uniform);
    glUniform1f(vertexColorLocation, value);
}

void Shader::setVec4(std::string uniform, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4)
{
    GLint vertexColorLocation = this->getUniformLocation(uniform);
    glUniform4f(vertexColorLocation, value1, value2, value3, value4);
}

void Shader::setVec3(std::string uniform, GLfloat value1, GLfloat value2, GLfloat value3)
{
    GLint vertexColorLocation = this->getUniformLocation(uniform);
    glUniform3f(vertexColorLocation, value1, value2, value3);
}

void Shader::setVec3(std::string uniform, glm::vec3& vec3)
{
    GLint vertexColorLocation = this->getUniformLocation(uniform);
    glUniform3f(vertexColorLocation, vec3.x, vec3.y, vec3.z);
}

void Shader::setProjectionAndView(glm::mat4& proj, glm::mat4& view)
{
    setMatrix4("projection", proj);
    setMatrix4("view", view);
}

void Shader::setMatrix4(std::string uniform, glm::mat4& matrix)
{
    GLint transformLoc = this->getUniformLocation(uniform);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setInt(std::string uniform, int value)
{
    GLint uniform_ = this->getUniformLocation(uniform);
    glUniform1i(uniform_, value);
}
