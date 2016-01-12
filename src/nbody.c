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


void NBody_tick(NBody* self, uint32_t dt) {
    Vector accelerations[NUM_STARS] = {{0.0f}};

    for (size_t i = 0; i < NUM_STARS; ++i) {
        Star* star_i = &self->stars[i];

        for (size_t j = i + 1; j < NUM_STARS; ++j) {
            Star* star_j = &self->stars[j];

            Vector delta = Vector_subtract(star_j->position, star_i->position);
            float distance = Vector_mag(delta) + 0.00001;

            Vector force = Vector_scale(delta, 0.001 / (distance * distance * distance));
            accelerations[i] = Vector_add(accelerations[i], Vector_scale(force, star_j->mass));
            accelerations[j] = Vector_add(accelerations[j], Vector_scale(force, -star_i->mass));
        }

        star_i->velocity = Vector_add(star_i->velocity, Vector_scale(accelerations[i], 0.001 * dt));
        star_i->position = Vector_add(star_i->position, Vector_scale(star_i->velocity, 0.001 * dt));
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


void NBody_step(NBody* self, uint32_t dt) {
    NBody_handle_events(self);
    NBody_tick(self, dt);
    NBody_draw(self);
}


void NBody_run(NBody* self) {
    log_info("Running nbody...");

    self->running = true;
    uint32_t lastTicks = SDL_GetTicks();
    while (self->running) {
        uint32_t currentTicks = SDL_GetTicks();
        NBody_step(self, currentTicks - lastTicks);

        lastTicks = currentTicks;
        SDL_Delay(16);
    }

    log_info("Shutting down..");
}
