#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"

int success;
char infoLog[512];

char shaderSrc[SHADER_MAX_LENGTH];

GLFWwindow* window;

// float vertices[] = {
//      1.0f,  1.0f, 0.0f, // top right
//      1.0f, -1.0f, 0.0f, // bottom right
//     -1.0f, -1.0f, 0.0f, // bottom left
//     -1.0f,  1.0f, 0.0f
// };
float vertices[] = {
     0.5f,  0.5f, 0.0f, // top right
     0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f
};
GLuint indicies[] = {
    0, 1, 3,
    1, 2, 3
};

const GLchar vertexShaderSource[] = {
#embed "shader.vert"
    , 0};
const GLchar fragmentShaderSource[] = {
#embed "shader.frag"
    , 0};

GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint shaderProgram;

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

GLuint createShader(const GLchar* src, GLuint type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

void createShaderProgram()
{
    GLuint vertexShader, fragmentShader;
    vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	printf("Error compiling vertex shader\n%s\n", infoLog);
    }

    fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	printf("Error compiling fragment shader\n%s\n", infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	printf("Error linking shader program: %s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
}

void vertexDataSetup()
{
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void draw()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

uint8_t initOpenGL()
{
    glfwLink(GL_MAJOR, GL_MINOR, GL_PROFILE);
    createWindow(W_WIDTH, W_HEIGH, W_TITLE);
    gladInit();

    createShaderProgram();
    vertexDataSetup();

    return 0;
}

void glCleanUp()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
