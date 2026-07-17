#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"

int main()
{
    initOpenGL();

    while(!windowShouldClose())
    {
	processInput();

	draw();

	glfwSwapBuffers(getGlfwWindow());
	glfwPollEvents();    
    }

    glCleanUp();
    return 0;
}
