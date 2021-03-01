#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders/Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "ShaderUtils.h"
#include "TextureCubeMap.h"
#include "TextureOne.h"

// Function prototypes
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	// время между текущим и последним кадрами
float lastFrame = 0.0f; // время последнего кадра

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
    

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("test");
    Shader skyboxShader("skybox");
    Shader lightShader("light");
    Shader containerShader("container");


    vector<float> vertices = ShaderUtils::getCube(1);
    VAO_VBO vao_vbo_container = ShaderUtils::loadTextureAndCoordinate(&vertices[0], vertices.size());

    vector<float> vertices_light = ShaderUtils::getCubeWithNormal();
    VAO_VBO vao_vbo_light = ShaderUtils::load2vec3(&vertices_light[0], vertices_light.size());


    glm::vec3 cubePositions[] = {
          glm::vec3(0.0f,  0.0f,  0.0f),
          glm::vec3(22.0f,  5.0f, 15.0f),
          glm::vec3(-1.5f, -2.2f, -2.5f),
          glm::vec3(-3.8f, -2.0f, -12.3f),
          glm::vec3(2.4f, -0.4f, -3.5f),
          glm::vec3(-1.7f,  3.0f, -7.5f),
          glm::vec3(1.3f, -2.0f, -2.5f),
          glm::vec3(1.5f,  2.0f, -2.5f),
          glm::vec3(1.5f,  0.2f, -1.5f),
          glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    vector<float> vertices2
	{
        5.0f, -0.5f,  5.0f,  100.0f, 00.0f,
       -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
       -5.0f, -0.5f, -5.0f,  0.0f, 100.0f,

        5.0f, -0.5f,  5.0f,  100.0f, 0.0f,
       -5.0f, -0.5f, -5.0f,  0.0f, 100.0f,
        5.0f, -0.5f, -5.0f,  100.0f, 100.0f
    };
    VAO_VBO vao_vbo_pol = ShaderUtils::loadTextureAndCoordinate(&vertices2[0], vertices2.size());
	
    Texture textureContainer = TextureOne("container.jpg");

    const vector<std::string> skybox
    {
        "sky\\right.jpg",
        "sky\\left.jpg",
        "sky\\top.jpg",
        "sky\\bottom.jpg",
        "sky\\front.jpg",
        "sky\\back.jpg"
    };

    Texture skyboxTexture = TextureCubeMap(skybox);

    vector<float> skyboxVertices = ShaderUtils::getCube();
    VAO_VBO vao_vbo_skybox = ShaderUtils::loadOnlyCoordinate(&skyboxVertices[0], skyboxVertices.size());
	
	

    glm::mat4 model = glm::mat4(1.0f); // сначала инициализируем единичную матрицу
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
	    const float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

    	
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthMask(GL_FALSE);
        skyboxShader.use();
        glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
        skyboxShader.setProjectionAndView(projection, view);
        glBindVertexArray(vao_vbo_skybox.VAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture.getTexture());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);

    	
        glBindTexture(GL_TEXTURE_2D, textureContainer.getTexture());
        glBindVertexArray(vao_vbo_container.VAO);
        containerShader.use();
        view = camera.getViewMatrix();
        containerShader.setProjectionAndView(projection, view);
        for (int i = 0; i < 8; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = glm::radians(20.0f * i);
            if (i == 0 || i % 2 == 0) {
                angle = sin(glfwGetTime());
            }
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            containerShader.setMatrix4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    	
    	
        ourShader.use();
        view = camera.getViewMatrix();
        ourShader.setProjectionAndView(projection, view);
        glBindVertexArray(vao_vbo_light.VAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[8]);
        float angle = glm::radians(20.0f * 8);
        //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMatrix4("model", model);
        ourShader.setVec3("objectColor", 0.0f, 0.5f, 0.31f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightPos", cubePositions[9]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.use();
        view = camera.getViewMatrix();
        lightShader.setProjectionAndView(projection, view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[9]);
        angle = glm::radians(20.0f * 9);
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMatrix4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        containerShader.use();
        view = camera.getViewMatrix();
        containerShader.setProjectionAndView(projection, view);
        glBindVertexArray(vao_vbo_pol.VAO);
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(20.0f, 1.0f, 20.0f));
        containerShader.setMatrix4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода\вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vao_vbo_light.disponse();
    vao_vbo_pol.disponse();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    float cameraSpeed = 2.5f * deltaTime;
	
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // перевернуто, так как y-координаты идут снизу вверх

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}
