#pragma once

#include <cstdbool>
#include "window.h"
#include "player.h"
#include "star.h"

#define NUM_STARS 512

class NBody {
public:
    NBody();
    ~NBody();
    void run();

private:
    Window* window;
    Player* player;
    bool running;
    Star stars[NUM_STARS];
    GLuint star_texture;

    void handle_event(SDL_Event event);
    void handle_events();
    void tick(uint32_t dt);
    void draw_star(Star star);
    void draw_stars();
    void draw();
    void step(uint32_t dt);
};
