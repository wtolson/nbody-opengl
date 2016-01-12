#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct {
    SDL_Window* window;
    SDL_GLContext context;
} Window;

Window* Window_new(void);
void Window_destroy(Window* self);
void Window_update(Window* self);
