#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "shared.h"
#include "colorscheme.h"
#include "color.h"

int success;
char infoLog[512];

char shaderSrc[SHADER_MAX_LENGTH];

GLFWwindow* window;

float vertices[] = {
     1.0f,  1.0f, 0.0f, // top right
     1.0f, -1.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f,  1.0f, 0.0f
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

typedef struct Point {
    float x;
    float y;
} Point;

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

    // atributes
    GLsizei stride = 3 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void setUniform4f(GLuint program, const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    int location = glGetUniformLocation(program, name);
    glUniform4f(location, v0, v1, v2, v3);
}

void setUniform2f(GLuint program, const GLchar* name, GLfloat v0, GLfloat v1)
{
    int location = glGetUniformLocation(program, name);
    glUniform2f(location, v0, v1);
}

void drawLine(double x1, double y1, double x2, double y2, float width, int color)
{
    double angle = atan2(y2-y1, x2-x1);
    double transAngle = angle+(PI/2);
    // top left
    vertices[9] =  x1+width*cos(transAngle)/2.0f;
    vertices[10] = y1+width*sin(transAngle)/2.0f;
    // bottom left
    vertices[6] =  x1-width*cos(transAngle)/2.0f;
    vertices[7] =  y1-width*sin(transAngle)/2.0f;
    // top right
    vertices[0] =  x2+width*cos(transAngle)/2.0f;
    vertices[1] =  y2+width*sin(transAngle)/2.0f;
    // bottom right
    vertices[3] =  x2-width*cos(transAngle)/2.0f;
    vertices[4] =  y2-width*sin(transAngle)/2.0f;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Color lineColor = getColor(color);
    setUniform4f(shaderProgram, "color", lineColor.r, lineColor.g, lineColor.b, 1.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawCurve(Point* points, int length, float width, int color)
{
    for (int i = 1; i<length; i++) {
	drawLine(points[i-1].x, points[i-1].y, points[i].x, points[i].y, width, color);
    }
}

void clearBack()
{
    Color color = getColor(BACK_COLOR);
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawGrid()
{
    // grid lines
    // horiz
    double xstep = 2.0f/GRIDH;
    double x = -1.0f+xstep;
    for (int i = 1; i<GRIDH; i++) {
	drawLine(x, 1.0f, x, -1.0f, LINE_WIDTH, GRID_COLOR);
	x+=xstep;
    }

    // vert
    double ystep = 2.0f/GRIDV;
    double y = -1.0f+ystep;
    for (int i = 1; i<GRIDV; i++) {
	drawLine(-1.0f, y, 1.0f, y, LINE_WIDTH, GRID_COLOR);
	y+=ystep;
    }

    // tick marks
    // horiz
    xstep = 2.0f/(GRIDH*TICK_COUNT);
    float gridStep = 2.0f/GRIDH;
    for (int i = 0; i<GRIDH; i++) {
	x = -1.0f + gridStep*i;
	for (int j = 0; j<TICK_COUNT; j++) {
	    drawLine(x, 0.0f+TICK_LENGTH/2, x, 0.0f-TICK_LENGTH/2, TICK_WIDTH, GRID_COLOR);
	    x+=xstep;
	}
    }

    // vert
    ystep = 2.0f/(GRIDV*TICK_COUNT);
    gridStep = 2.0f/GRIDV;
    for (int i = 0; i<GRIDV; i++) {
	y = -1.0f + gridStep*i;
	for (int j = 0; j<TICK_COUNT; j++) {
	    drawLine(0.0f+TICK_LENGTH/2, y, 0.0f-TICK_LENGTH/2, y, TICK_WIDTH, GRID_COLOR);
	    y+=ystep;
	}
    }
}

void draw()
{
    clearBack();

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    drawGrid();

    // debug sine
    Point curve[HORIZ_PREC];
    double step = (8*PI)/(HORIZ_PREC);
    double xstep = 2.0f/HORIZ_PREC;
    double x = -1.0f;
    double t = 0;
    for (int i = 0; i<HORIZ_PREC; i++) {
	curve[i].x = x;
	x += xstep;
	curve[i].y = sin(t);
	t+=step;
    }

    drawCurve(curve, LENGTH(curve), CURVE_WIDTH, CURVE1_COLOR);
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

void processInput()
{
}

void glCleanUp()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
