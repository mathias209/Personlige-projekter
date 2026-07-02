#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "render.h"

int main()
{
    initOpenGL();

    while(!windowShouldClose())
    {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(getGlfwWindow());
	glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
