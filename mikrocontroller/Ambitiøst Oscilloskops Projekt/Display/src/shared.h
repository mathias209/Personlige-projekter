#ifndef SHARED_H
#define SHARED_H

#include <GLFW/glfw3.h>

// color
typedef struct Color {
    float r;
    float g;
    float b;
    float a;
} Color;

#define C_BLACK     0
#define C_WHITE     1
#define C_RED       2
#define C_GREEN     3
#define C_BLUE      4
#define C_YELLOW    5
#define C_PURPLE    6
#define C_CYAN      7
#define C_LIGHTGREY 8
#define C_DARKGREY  9
#define C_PINK      10
#define C_TRANS     11

// macros
#define LENGTH(ARR) sizeof(ARR)/sizeof(ARR[0])

// constants
#define PI 3.1415926535897932384626433f
#define PATH "/home/mathias/Personlige-projekter/mikrocontroller/Ambitiøst Oscilloskops Projekt/Display/"

// config
#define GL_MAJOR 4
#define GL_MINOR 6
#define GL_PROFILE GLFW_OPENGL_CORE_PROFILE

#define W_WIDTH 800
#define W_HEIGH 600
#define W_TITLE "Oscilloskop"

#define SHADER_MAX_LENGTH 5000

#define TEXT_FILTER GL_NEAREST

#define GRIDH 10
#define GRIDV 8
#define CURVE_WIDTH 0.002f
#define LINE_WIDTH 0.0015f
#define TICK_LENGTH 0.02f
#define TICK_WIDTH 0.002f
#define TICK_COUNT 5

#define HORIZ_PREC 500

#endif
