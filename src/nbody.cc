#include <iostream>
#include <SDL2/SDL.h>
#include <glm/geometric.hpp>
#include <glm/gtx/string_cast.hpp>

#include "log.h"
#include "nbody.h"


NBody::NBody() {
    this->window = new Window();
    this->player = new Player();
    this->player->position = glm::vec3(0.0f, 0.0f, 5.0f);

    // Turn on alpha blending for transparency
    glEnable(GL_BLEND);  // Turn Blending On
    glEnable(GL_TEXTURE_2D);  // Turn on textures
    glDisable(GL_DEPTH_TEST);  // Turn Depth Testing Off
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // Load up star texture
    glGenTextures(1, &this->star_texture);
    glBindTexture(GL_TEXTURE_2D, this->star_texture);

    float* pixels = Star::load_texture();
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
        this->stars[i] = Star::random();
    }
}


NBody::~NBody() {
    if (this->star_texture != 0) {
        glDeleteTextures(1, &this->star_texture);
        this->star_texture = 0;
    }

    if (this->player != NULL) {
        delete this->player;
        this->player = NULL;
    }

    if (this->window != NULL) {
        delete this->window;
        this->window = NULL;
    }
}


void NBody::handle_event(SDL_Event event) {
    if(event.type == SDL_QUIT) {
        this->running = false;
        return;
    }

    if (event.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym ) {
            case SDLK_ESCAPE: this->running = false;
            default: break;
        }
        return;
    }
}


void NBody::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        this->handle_event(event);
    }

    const uint8_t *keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_UP]) {
        this->player->rotate(0.0f, 1.0f);
    }

    if (keystates[SDL_SCANCODE_DOWN]) {
        this->player->rotate(0.0f, -1.0f);
    }

    if (keystates[SDL_SCANCODE_RIGHT]) {
        this->player->rotate(1.0f, 0.0f);
    }

    if (keystates[SDL_SCANCODE_LEFT]) {
        this->player->rotate(-1.0f, 0.0f);
    }
}


void NBody::tick(uint32_t dt) {
    this->player->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 accelerations[NUM_STARS];

    // Update player
    for (size_t i = 0; i < NUM_STARS; ++i) {
        Star* star = &this->stars[i];

        glm::vec3 delta = star->position - this->player->position;
        float distance =  glm::length(delta) + 0.00001f;  // Add small amount to avoid collision

        glm::vec3 force = 0.001f * delta / (distance * distance * distance);
        this->player->acceleration += star->mass * force;
    }

    this->player->velocity += 0.001f * dt * this->player->acceleration;
    this->player->position += 0.001f * dt * this->player->velocity;

    // Update stars
    for (size_t i = 0; i < NUM_STARS; ++i) {
        Star* star_i = &this->stars[i];

        for (size_t j = i + 1; j < NUM_STARS; ++j) {
            Star* star_j = &this->stars[j];

            glm::vec3 delta =star_j->position - star_i->position;
            float distance =  glm::length(delta) + 0.00001f;  // Add small amount to avoid collision

            glm::vec3 force = 0.001f * delta / (distance * distance * distance);
            accelerations[i] += star_j->mass * force;
            accelerations[j] -= star_i->mass * force;
        }

        // std::cout << glm::to_string(accelerations[i]) << " ";
        // std::cout << glm::to_string(star_i->velocity) << " ";
        // std::cout << glm::to_string(star_i->position) << std::endl;

        star_i->velocity += 0.001f * dt * accelerations[i];
        star_i->position += 0.001f * dt * star_i->velocity;
    }
}


void NBody::draw_star(Star star) {
    // Set stars color
    if (star.mass < 0.5f) {
        float lum = star.mass + 0.5f;
        float lum_2 = lum * lum;
        glColor4f(lum, lum_2, lum_2, 1.0f);
    } else {
        float lum = (1.0f - star.mass) + 0.5f;
        float lum_2 = lum * lum;
        glColor4f(lum_2, lum_2, lum, 1.0f);
    }

    glPushMatrix();
        // Translate to star's center
        glTranslatef(star.position.x, star.position.y, star.position.z);

        // Face stars towards camera
        this->player->unrotate_camera();

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


void NBody::draw_stars() {
    // Select Our Texture
    glBindTexture(GL_TEXTURE_2D, this->star_texture);

    for (size_t i = 0; i < NUM_STARS; ++i) {
        this->draw_star(this->stars[i]);
    }
}


void loadPerspective(float fovyInDegrees, float znear, float zfar) {
    float ymax = znear * tanf(fovyInDegrees * M_PI / 360.0f);
    float xmax = ymax * (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    glFrustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}


void NBody::draw() {
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    loadPerspective(60.0f, 0.0001f, 100.0f);

    // Reset model view projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move to camera to player
    this->player->move_camera();

    this->draw_stars();
    this->window->update();
}


void NBody::step(uint32_t dt) {
    this->handle_events();
    this->tick(dt);
    this->draw();
}


void NBody::run() {
    log_info("Running nbody...");

    this->running = true;
    uint32_t lastTicks = SDL_GetTicks();

    while (this->running) {
        uint32_t currentTicks = SDL_GetTicks();
        this->step(currentTicks - lastTicks);

        lastTicks = currentTicks;
        SDL_Delay(16);
    }

    log_info("Shutting down.");
}