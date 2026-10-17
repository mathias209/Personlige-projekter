#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "shared.h"
#include "colorscheme.h"
#include "color.h"

int success;
char infoLog[512];

char shaderSrc[SHADER_MAX_LENGTH];

GLFWwindow* window;

float lineVertices[] = {
     1.0f,  1.0f, 0.0f, // top right
     1.0f, -1.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f,  1.0f, 0.0f  // top left
};
GLuint lineIndicies[] = {
    0, 1, 3,
    1, 2, 3
};

const GLchar lineVertSrc[] = {
#embed "line.vert"
    , 0};
const GLchar lineFragSrc[] = {
#embed "line.frag"
    , 0};

GLuint lineVAO;
GLuint lineVBO;
GLuint lineEBO;
GLuint lineProgram;

float texVertices[] = {
     // positions        // texture coords
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
};
GLuint texIndicies[] = {
    0, 1, 3,
    1, 2, 3
};

const GLchar texVertSrc[] = {
#embed "tex.vert"
    , 0};

const GLchar texFragSrc[] = {
#embed "tex.frag"
    , 0};

GLuint texVAO;
GLuint texVBO;
GLuint texEBO;
GLuint texProgram;

unsigned int bitmapFontTex;

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct Image {
    unsigned char *data;
    int with;
    int height;
    int nrChannels;
} Image;

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

void createShaderProgram(unsigned int* program, const char* vertSrc, const char* fragSrc)
{
    GLuint vertexShader, fragmentShader;
    vertexShader = createShader(vertSrc, GL_VERTEX_SHADER);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	printf("Error compiling vertex shader\n%s\n", infoLog);
    }

    fragmentShader = createShader(fragSrc, GL_FRAGMENT_SHADER);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	printf("Error compiling fragment shader\n%s\n", infoLog);
    }

    *program = glCreateProgram();
    glAttachShader(*program, vertexShader);
    glAttachShader(*program, fragmentShader);
    glLinkProgram(*program);
    glGetProgramiv(*program, GL_LINK_STATUS, &success);
    if (!success) {
	glGetProgramInfoLog(*program, 512, NULL, infoLog);
	printf("Error linking shader program: %s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void lineVertexDataSetup()
{
    glGenVertexArrays(1, &lineVAO);

    glGenBuffers(1, &lineVBO);
    glGenBuffers(1, &lineEBO);

    glBindVertexArray(lineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineIndicies), lineIndicies, GL_STATIC_DRAW);

    // atributes
    GLsizei stride = 3 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void texVertexDataSetup()
{
    glGenVertexArrays(1, &texVAO);

    glGenBuffers(1, &texVBO);
    glGenBuffers(1, &texEBO);

    glBindVertexArray(texVAO);

    glBindBuffer(GL_ARRAY_BUFFER, texVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texVertices), texVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texIndicies), texIndicies, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


Image loadImage(char* filename)
{
    Image result;
    result.data = stbi_load(filename, &result.with, &result.height, &result.nrChannels, 0);
    if (!result.data)
	printf("failed to load texture %s\n", filename);
    return result;
}

void fontTextureSetup()
{
    glGenTextures(1, &bitmapFontTex);
    glBindTexture(GL_TEXTURE_2D, bitmapFontTex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[4];
    getColorVec4(C_TRANS, borderColor);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXT_FILTER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXT_FILTER);

    stbi_set_flip_vertically_on_load(true);
    // dimensions not power of 2
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    Image textureImage = loadImage(PATH"terminus-u32b.png");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.with, textureImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data);
    stbi_image_free(textureImage.data);
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
    lineVertices[9] =  x1+width*cos(transAngle)/2.0f;
    lineVertices[10] = y1+width*sin(transAngle)/2.0f;
    // bottom left
    lineVertices[6] =  x1-width*cos(transAngle)/2.0f;
    lineVertices[7] =  y1-width*sin(transAngle)/2.0f;
    // top right
    lineVertices[0] =  x2+width*cos(transAngle)/2.0f;
    lineVertices[1] =  y2+width*sin(transAngle)/2.0f;
    // bottom right
    lineVertices[3] =  x2-width*cos(transAngle)/2.0f;
    lineVertices[4] =  y2-width*sin(transAngle)/2.0f;

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Color lineColor = getColor(color);
    setUniform4f(lineProgram, "color", lineColor.r, lineColor.g, lineColor.b, 1.0f);

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

    glUseProgram(lineProgram);
    glBindVertexArray(lineVAO);

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

    glBindTexture(GL_TEXTURE_2D, bitmapFontTex);
    glUseProgram(texProgram);
    Color textColor = getColor(C_CYAN);
    setUniform4f(texProgram, "textColor", textColor.r, textColor.g, textColor.b, textColor.a);
    glBindVertexArray(texVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

uint8_t initOpenGL()
{
    glfwLink(GL_MAJOR, GL_MINOR, GL_PROFILE);
    createWindow(W_WIDTH, W_HEIGH, W_TITLE);
    gladInit();

    createShaderProgram(&lineProgram, lineVertSrc, lineFragSrc);
    lineVertexDataSetup();

    createShaderProgram(&texProgram, texVertSrc, texFragSrc);
    texVertexDataSetup();
    fontTextureSetup();

    return 0;
}

void processInput()
{
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	glfwSetWindowShouldClose(window, 1);
}

void glCleanUp()
{
    glDeleteVertexArrays(1, &lineVAO);
    glDeleteBuffers(1, &lineVBO);
    glDeleteBuffers(1, &lineEBO);
    glDeleteProgram(lineProgram);

    glDeleteVertexArrays(1, &texVAO);
    glDeleteBuffers(1, &texVBO);
    glDeleteBuffers(1, &texEBO);
    glDeleteProgram(texProgram);

    glfwTerminate();
}
