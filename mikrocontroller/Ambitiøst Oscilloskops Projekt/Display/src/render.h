#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

// keeping so i dont have to copy-paste tehe
// void glfwLink(uint8_t major, uint8_t minor, uint32_t profile);
// uint8_t createWindow(uint16_t width, uint16_t height, char* title);
// uint8_t gladInit();

uint8_t windowShouldClose();
GLFWwindow* getGlfwWindow();
uint8_t initOpenGL();
void draw();
void glCleanUp();

#endif
