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

    // Turn on alpha blending for transparency
    glEnable(GL_BLEND);  // Turn Blending On
    glEnable(GL_TEXTURE_2D);  // Turn on textures
    glDisable(GL_DEPTH_TEST);  // Turn Depth Testing Off
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // Load up star texture
    glGenTextures(1, &self->star_texture);
    glBindTexture(GL_TEXTURE_2D, self->star_texture);

    float* pixels = load_star_texture();
    glTexImage2D(
        GL_TEXTURE_2D,      // target
        0,                  // level
        GL_ALPHA,           // internalFormat
        STAR_TEXTURE_SIZE,  // width
        STAR_TEXTURE_SIZE,  // height
        0,                  // border
        GL_ALPHA,           // format
        GL_FLOAT,           // type
        pixels              // data
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    free(pixels);

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
    Vector accelerations[NUM_STARS] = {{0.0f, 0.0f, 0.0f}};

    for (size_t i = 0; i < NUM_STARS; ++i) {
        Star* star_i = &self->stars[i];

        for (size_t j = i + 1; j < NUM_STARS; ++j) {
            Star* star_j = &self->stars[j];

            Vector delta = Vector_subtract(star_j->position, star_i->position);
            float distance = Vector_mag(delta) + 0.00001;  // Add small amount to avoid collision

            Vector force = Vector_scale(delta, 0.001 / (distance * distance * distance));
            accelerations[i] = Vector_add(accelerations[i], Vector_scale(force, star_j->mass));
            accelerations[j] = Vector_add(accelerations[j], Vector_scale(force, -star_i->mass));
        }

        star_i->velocity = Vector_add(star_i->velocity, Vector_scale(accelerations[i], 0.001 * dt));
        star_i->position = Vector_add(star_i->position, Vector_scale(star_i->velocity, 0.001 * dt));
    }
}


void NBody_draw_star(NBody* self, Star star) {
    // Set stars color
    if (star.mass < 0.5) {
        float lum = star.mass + 0.5;
        float lum_2 = lum * lum;
        glColor4f(lum, lum_2, lum_2, 1.0f);
    } else {
        float lum = (1.0 - star.mass) + 0.5;
        float lum_2 = lum * lum;
        glColor4f(lum_2, lum_2, lum, 1.0f);
    }

    glPushMatrix();
        // Translate to star's center
        glTranslatef(star.position.x, star.position.y, star.position.z);

        // Scale star by mass
        float scale = 0.08f * sqrtf(star.mass);
        glScalef(scale, scale, scale);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
        glEnd();
    glPopMatrix();
}


void NBody_draw_stars(NBody* self) {
    // Select Our Texture
    glBindTexture(GL_TEXTURE_2D, self->star_texture);

    for (size_t i = 0; i < NUM_STARS; ++i) {
        NBody_draw_star(self, self->stars[i]);
    }
}


void NBody_draw(NBody* self) {
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset matrix
    glLoadIdentity();

    // Zoom out a little
    float scale = 0.5f;
    glScalef(scale, scale, scale);

    NBody_draw_stars(self);
    Window_update(self->window);
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
