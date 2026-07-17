#include "shared.h"

Color colors[] = {
    {0.0f, 0.0f, 0.0f}, // black
    {1.0f, 1.0f, 1.0f}, // white
    {1.0f, 0.0f, 0.0f}, // red
    {0.0f, 1.0f, 0.0f}, // green
    {0.0f, 0.0f, 1.0f}, // blue
    {1.0f, 1.0f, 0.0f}, // yellow
    {1.0f, 0.0f, 1.0f}, // purple
    {0.0f, 1.0f, 1.0f}, // cyan
    {0.74f, 0.74f, 0.74f}, // light grey
    {0.19f, 0.19f, 0.19f}, // dark grey
    {1.0f, 0.75f, 0.80}, // pink
};

Color getColor(int color)
{
    return colors[color];
}
