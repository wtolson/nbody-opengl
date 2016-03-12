#pragma once

#include <cstdbool>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Window {
public:
    Window();
    ~Window();
    void update();

private:
    SDL_Window* window;
    SDL_GLContext context;
};
