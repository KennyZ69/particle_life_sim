/* app.c */

#include "in/app.h"
#include "in/particle.h"
#include "in/util.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_GLContext glContext = NULL;

bool init (const char *title) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		fprintf(stderr, "Could not create context: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_GL_SetSwapInterval(1);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark gray for background
	glEnable(GL_DEPTH_TEST);

	return true;
}

void run_2D() {
	init_Particles_2D();
	i8 running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						running = false;
						break;
					case SDLK_r:
						// reset particles somehow
						reset();
						break;
					default:
						break;
				}
			} else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					int width, height;
					SDL_GetWindowSize(window, &width, &height);
					glViewport(0, 0, width, height);
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		update_Particles_2D(1/60.0f);
		render_Particles_2D();

		SDL_GL_SwapWindow(window);
		SDL_Delay(16);
	}
}

void cleanup() {
	if (glContext) {
		SDL_GL_DeleteContext(glContext);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}
