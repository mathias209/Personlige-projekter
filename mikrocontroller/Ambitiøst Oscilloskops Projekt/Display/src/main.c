#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"

int main()
{
    initOpenGL();

    while(!windowShouldClose())
    {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	draw();

	glfwSwapBuffers(getGlfwWindow());
	glfwPollEvents();    
    }

    glCleanUp();
    return 0;
}
