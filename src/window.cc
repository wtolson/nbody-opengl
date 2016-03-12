#include "log.h"
#include "window.h"


bool init_opengl() {
    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Check for error
    if(glGetError() != GL_NO_ERROR) {
        return false;
    }

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Check for error
    if(glGetError() != GL_NO_ERROR) {
        return false;
    }

    // Initialize clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Check for error
    if(glGetError() != GL_NO_ERROR) {
        return false;
    }

    return true;
}


Window::Window() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return;
    }

    // Use OpenGL 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    this->window = SDL_CreateWindow(
        "NBody",                              // title
        SDL_WINDOWPOS_UNDEFINED,              // x
        SDL_WINDOWPOS_UNDEFINED,              // y
        WINDOW_WIDTH,                         // w
        WINDOW_HEIGHT,                        // h
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN  // flags
    );

    if (this->window == NULL) {
        log_error("Window could not be created! SDL_Error: %s", SDL_GetError());
        return;
    }

    this->context = SDL_GL_CreateContext(this->window);
    if(this->context == NULL) {
        log_error("OpenGL context could not be created! SDL_Error: %s", SDL_GetError());
        return;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        log_warn("Unable to set VSync! SDL Error: %s", SDL_GetError());
    }

    if (!init_opengl()) {
        log_error("Unable to initialize OpenGL!");
        return;
    }
}


Window::~Window() {
    if (this->context != NULL) {
        SDL_GL_DeleteContext(this->context);
        this->context = NULL;
    }

    if (this->window != NULL) {
        SDL_DestroyWindow(this->window);
        this->window = NULL;
    }

    SDL_Quit();
}

void Window::update() {
    //Update screen
    SDL_GL_SwapWindow(this->window);
}
