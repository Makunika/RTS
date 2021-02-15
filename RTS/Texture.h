#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "stb_image.h"
#include "Utils.h"
using namespace std;

class Texture
{
private:
    unsigned int texture;
    int width;
    int height;
public: 

	Texture(string filename) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Устанавливаем параметры наложения и фильтрации текстур (для текущего связанного объекта текстуры)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Загрузка и генерация текстуры
        int nrChannels;
        unsigned char* data = stbi_load(Utils::getImagePathString(filename).c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

	}

    unsigned int getTexture() {
        return texture;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }
};

