#ifndef _nbody_window_h
#define _nbody_window_h


#include <stdbool.h>
#include <SDL2/SDL.h>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
} Window;


Window* Window_new();
void Window_destroy(Window* self);
void Window_fill(Window* self, uint32_t color);
void Window_render(Window* self);

#endif
