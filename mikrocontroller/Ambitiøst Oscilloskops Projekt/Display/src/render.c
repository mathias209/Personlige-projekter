#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"

GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void glfwLink(uint8_t major, uint8_t minor, uint32_t profile)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

uint8_t createWindow(uint16_t width, uint16_t height, char* title)
{
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
	puts("Failed to create GLFW window\n");
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 0;
}

uint8_t windowShouldClose()
{
    return glfwWindowShouldClose(window);
}

uint8_t gladInit()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
	puts("Failed to initialize GLAD\n");
	return -1;
    }
    return 0;
}

GLFWwindow* getGlfwWindow()
{
    return window;
}

uint8_t initOpenGL()
{
    glfwLink(GL_MAJOR, GL_MINOR, GL_PROFILE);
    createWindow(W_WIDTH, W_HEIGH, W_TITLE);
    gladInit();

    return 0;
}
