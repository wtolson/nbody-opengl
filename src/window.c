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


Window* Window_new() {
    Window* self = calloc(1, sizeof(Window));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return NULL;
    }

    // Use OpenGL 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    self->window = SDL_CreateWindow(
        "NBody",                              // title
        SDL_WINDOWPOS_UNDEFINED,              // x
        SDL_WINDOWPOS_UNDEFINED,              // y
        WINDOW_WIDTH,                         // w
        WINDOW_HEIGHT,                        // h
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN  // flags
    );

    if (self->window == NULL) {
        log_error("Window could not be created! SDL_Error: %s", SDL_GetError());
        goto error;
    }

    self->context = SDL_GL_CreateContext(self->window);
    if(self->context == NULL) {
        log_error("OpenGL context could not be created! SDL_Error: %s", SDL_GetError());
        goto error;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        log_warn("Unable to set VSync! SDL Error: %s", SDL_GetError());
    }

    if (!init_opengl()) {
        log_error("Unable to initialize OpenGL!");
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

    if (self->context != NULL) {
        SDL_GL_DeleteContext(self->context);
        self->context = NULL;
    }

    if (self->window != NULL) {
        SDL_DestroyWindow(self->window);
        self->window = NULL;
    }

    SDL_Quit();
    free(self);
}

void Window_update(Window* self) {
    //Update screen
    SDL_GL_SwapWindow(self->window);
}
