#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

void glfwLink(uint8_t major, uint8_t minor, uint32_t profile);
uint8_t createWindow(uint16_t width, uint16_t height, char* title);
uint8_t windowShouldClose();
uint8_t gladInit();
GLFWwindow* getGlfwWindow();
uint8_t initOpenGL();

#endif
