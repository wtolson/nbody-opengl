#include <stdio.h>
#include <SDL2/SDL.h>

#include "log.h"
#include "nbody.h"


NBody* NBody_new() {
    NBody* self = malloc(sizeof(NBody));
    self->running = false;

    self->window = Window_new();
    if (self->window == NULL) {
        goto error;
    }

    for (size_t i = 0; i < NUM_STARS; ++i) {
        self->stars[i] = Star_random();
    }

    return self;

error:
    NBody_destroy(self);
    return NULL;
}


void NBody_destroy(NBody* self) {
    Window_destroy(self->window);
    free(self);
}


void NBody_handle_event(NBody* self, SDL_Event event) {
    if(event.type == SDL_QUIT) {
        self->running = false;
        return;
    }

    if (event.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym ) {
            case SDLK_ESCAPE: self->running = false;
            default: break;
        }
        return;
    }
}


void NBody_handle_events(NBody* self) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        NBody_handle_event(self, event);
    }
}


void NBody_draw_stars(NBody* self) {
    SDL_Rect rect;
    uint32_t color = SDL_MapRGB(self->window->surface->format, 0xFF, 0xFF, 0xFF);

    for (size_t i = 0; i < NUM_STARS; ++i) {
        Star star = self->stars[i];
        Vector position = Vector_scale(star.position, WINDOW_WIDTH);
        rect.x = (int) position.x;
        rect.y = (int) position.y;
        rect.w = 1;
        rect.h = 1;
        SDL_FillRect(self->window->surface, &rect, color);
    }
}


void NBody_draw(NBody* self) {
    Window_fill(self->window, 0);
    NBody_draw_stars(self);
    Window_render(self->window);
}


void NBody_step(NBody* self) {
    NBody_handle_events(self);
    NBody_draw(self);
    SDL_Delay(1);
}


void NBody_run(NBody* self) {
    log_info("Running nbody...");

    self->running = true;
    while (self->running) {
        NBody_step(self);
    }

    log_info("Shutting down..");
}
