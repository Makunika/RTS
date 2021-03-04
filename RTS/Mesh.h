#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shaders/Shader.h"

using namespace std;

struct Vertex {
    // Позиция
    glm::vec3 position;
    // Нормаль
    glm::vec3 normal;
    // Текстурные координаты
    glm::vec2 tex_coords;
    // Касательный вектор
    glm::vec3 tangent;
    // Вектор бинормали (вектор, перпендикулярный касательному вектору и вектору нормали)
    glm::vec3 bitangent;
};

struct Texture_ {
    unsigned int id;
    string type;
    string path;
};


class Mesh
{
public:
    vector<Vertex>          vertices;
    vector<unsigned int>    indices;
    vector<Texture_>        textures;
    unsigned int            VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture_> textures);
    void draw(Shader& shader);
private:

    unsigned int VBO, EBO;

    void setupMesh();
};

inline Mesh::Mesh(vector<Vertex> vertices, vector<unsigned> indices, vector<Texture_> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

inline void Mesh::draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // активируем соответствующий текстурный юнит перед привязкой
        // Получаем номер текстуры (значение N в diffuse_textureN)
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // конвертируем unsigned int в строку
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // конвертируем unsigned int в строку
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // конвертируем unsigned int в строку

        shader.setFloat(name + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // Отрисовываем меш
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

inline void Mesh::setupMesh()
{
    // Создаем буферные объекты/массивы
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Загружаем данные в вершинный буфер
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Самое замечательное в структурах то, что расположение в памяти их внутренних переменных является последовательным.
    // Смысл данного трюка в том, что мы можем просто передать указатель на структуру, и она прекрасно преобразуется в массив данных с элементами типа glm::vec3 (или glm::vec2), который затем будет преобразован в массив данных float, ну а в конце – в байтовый массив
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Устанавливаем указатели вершинных атрибутов

    // Координаты вершин
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Нормали вершин
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Текстурные координаты вершин
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

    // Касательный вектор вершины
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    // Вектор бинормали вершины
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

