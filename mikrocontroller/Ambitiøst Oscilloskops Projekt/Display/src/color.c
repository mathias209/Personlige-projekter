#include "shared.h"

Color colors[] = {
    {0.0f,  0.0f,  0.0f,  1.0f}, // black
    {1.0f,  1.0f,  1.0f,  1.0f}, // white
    {1.0f,  0.0f,  0.0f,  1.0f}, // red
    {0.0f,  1.0f,  0.0f,  1.0f}, // green
    {0.0f,  0.0f,  1.0f,  1.0f}, // blue
    {1.0f,  1.0f,  0.0f,  1.0f}, // yellow
    {1.0f,  0.0f,  1.0f,  1.0f}, // purple
    {0.0f,  1.0f,  1.0f,  1.0f}, // cyan
    {0.74f, 0.74f, 0.74f, 1.0f}, // light grey
    {0.19f, 0.19f, 0.19f, 1.0f}, // dark grey
    {1.0f,  0.27f, 0.64f, 1.0f}, // pink
    {0.0f,  0.0f,  0.0f,  0.0f}, // transparent
};

Color getColor(int color)
{
    return colors[color];
}

void getColorVec4(int color, float* dest)
{
    dest[0] = colors[color].r;
    dest[1] = colors[color].g;
    dest[2] = colors[color].b;
    dest[3] = colors[color].a;
}
