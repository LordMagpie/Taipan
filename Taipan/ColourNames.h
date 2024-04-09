// ColourNames.h

#pragma once

#include <SDL2/SDL.h>

enum DOSColor {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};

// RGB values for the DOS 16-color palette
const SDL_Color dosColors[] = {
    {0, 0, 0},          // BLACK
    {0, 0, 170},        // BLUE
    {0, 170, 0},        // GREEN
    {0, 170, 170},      // CYAN
    {170, 0, 0},        // RED
    {170, 0, 170},      // MAGENTA
    {170, 85, 0},       // BROWN
    {170, 170, 170},    // LIGHT_GRAY
    {85, 85, 85},       // DARK_GRAY
    {85, 85, 255},      // LIGHT_BLUE
    {85, 255, 85},      // LIGHT_GREEN
    {85, 255, 255},     // LIGHT_CYAN
    {255, 85, 85},      // LIGHT_RED
    {255, 85, 255},     // LIGHT_MAGENTA
    {255, 255, 85},     // YELLOW
    {255, 255, 255}     // WHITE
};