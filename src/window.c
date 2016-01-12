#include "log.h"
#include "window.h"


Window* Window_new() {
    Window* self = malloc(sizeof(Window));
    memset(self, 0, sizeof(Window));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return NULL;
    }

    self->window = SDL_CreateWindow(
        "NBody",                  // title
        SDL_WINDOWPOS_UNDEFINED,  // x
        SDL_WINDOWPOS_UNDEFINED,  // y
        WINDOW_WIDTH,             // w
        WINDOW_HEIGHT,            // h
        SDL_WINDOW_SHOWN          // flags
    );

    if (self->window == NULL) {
        log_error("Window could not be created! SDL_Error: %s", SDL_GetError());
        goto error;
    }

    self->renderer = SDL_CreateRenderer(
        self->window,                                         // window
        -1,                                                   // index
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  // flags
    );

    if(self->renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    self->surface = SDL_CreateRGBSurface(
        0,              // flags
        WINDOW_WIDTH,   // width
        WINDOW_HEIGHT,  // height
        32,             // depth
        0,              // Rmask
        0,              // Gmask
        0,              // Bmask
        0               // Amask
    );

    if(self->surface == NULL) {
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    self->texture = SDL_CreateTextureFromSurface(
        self->renderer,
        self->surface
    );

    if(self->texture == NULL) {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    return self;

error:
    Window_destroy(self);
    return NULL;
}


void Window_destroy(Window* self) {
    if (self == NULL) {
        return;
    }

    if (self->texture != NULL) {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
    }

    if (self->surface != NULL) {
        SDL_FreeSurface(self->surface);
        self->surface = NULL;
    }

    if (self->renderer != NULL) {
        SDL_DestroyRenderer(self->renderer);
        self->renderer = NULL;
    }

    if (self->window != NULL) {
        SDL_DestroyWindow(self->window);
        self->window = NULL;
    }

    SDL_Quit();
    free(self);
}


void Window_fill(Window* self, uint32_t color) {
    SDL_FillRect(self->surface, NULL, color);
}


void Window_render(Window* self) {
    SDL_UpdateTexture(self->texture, NULL, self->surface->pixels, self->surface->pitch);
    SDL_RenderCopy(self->renderer, self->texture, NULL, NULL);
    SDL_RenderPresent(self->renderer);
}
