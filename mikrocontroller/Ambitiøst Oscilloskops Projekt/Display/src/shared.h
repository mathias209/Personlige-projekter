#ifndef SHARED_H
#define SHARED_H

#include <GLFW/glfw3.h>

// color
typedef struct Color {
    float r;
    float g;
    float b;
} Color;

#define BLACK 0
#define WHITE 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define YELLOW 5
#define PURPLE 6
#define CYAN 7
#define LIGHTGREY 8
#define DARKGREY 9
#define PINK 10

// macros
#define LENGTH(ARR) sizeof(ARR)/sizeof(ARR[0])

// constants
#define PI 3.1415926535897932384626433f

// config
#define GL_MAJOR 4
#define GL_MINOR 6
#define GL_PROFILE GLFW_OPENGL_CORE_PROFILE

#define W_WIDTH 800
#define W_HEIGH 600
#define W_TITLE "Oscilloskop"

#define SHADER_MAX_LENGTH 5000

#define GRIDH 10
#define GRIDV 8
#define CURVE_WIDTH 0.002f
#define LINE_WIDTH 0.0015f
#define TICK_LENGTH 0.02f
#define TICK_WIDTH 0.002f
#define TICK_COUNT 5

#define HORIZ_PREC 500

#endif
