#pragma once

#include <GLFW/glfw3.h>

#include "Camera.h"

struct State
{
	int width; // ширина окна
	int height; // высота окна

	float lastX;
	float lastY;

	bool firstMouse = true;
	float deltaTime = 0.0f;	// время между текущим и последним кадрами
	float lastFrame = 0.0f; // время последнего кадра
	bool cursorLocked = false;

	Camera* camera;
	GLFWwindow* window;
};
