/* util.h */

#pragma once

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 1280

typedef unsigned char i8;
typedef unsigned short i16;
typedef unsigned int i32;
typedef unsigned long i64;

#define true 1
#define false 0
#define bool i8

typedef struct {
	float r, g, b;
	i8 idx;
} Color;

typedef struct {
	float x, y;
} Vec2D;

#define BOUNDS 8.0f
#define PART_SEGMENTS 32
// #define GRAVITY 0.981f
#define REPULSION 5.1f
#define GRAVITY 9.81f
// #define GRAVITY 3.0f
#define ENERGY_LOSS 0.95f
#define DELTA 0.016f


static inline Vec2D Vec2D_add(Vec2D a, Vec2D b) {
	return (Vec2D){a.x + b.x, a.y + b.y};
}

static inline Vec2D Vec2D_sub(Vec2D a, Vec2D b) {
	return (Vec2D){a.x - b.x, a.y - b.y};
}

static inline Vec2D Vec2D_mult(Vec2D v, float scalar) {
	return (Vec2D){v.x * scalar, v.y * scalar};
}

static inline Vec2D Vec2D_norm(Vec2D v) {
	float dist = sqrtf(v.x * v.x + v.y * v.y);
	return dist > 0 ? (Vec2D){v.x / dist, v.y / dist} : (Vec2D){0, 0};
}

static inline float randf(float min, float max) {
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}

static inline Color color(float r, float g, float b, i8 i) {
	Color c = {r, g, b, i};
	return c;
}

static inline Color randColor(i8 i) {
	return color(randf(0.0f, 1.0f), randf(0.0f, 1.0f), randf(0.0f, 1.0f), i);
}

// Idk how to do this properly, I need to draw a simple square outline for the bounds to see the used space
static inline void drawBounds() {
	glColor3f(1, 1, 1);
	glLineWidth(2.0f);

	glBegin(GL_LINE_LOOP);

		glVertex2f(-BOUNDS, -BOUNDS);
		glVertex2f(BOUNDS, -BOUNDS);
		glVertex2f(BOUNDS, BOUNDS);
		glVertex2f(-BOUNDS, BOUNDS);

	glEnd();
}

#define COLOR_COUNT 2

static inline Color *init_colors() {
	Color *colors = malloc(COLOR_COUNT * sizeof(Color));
	for (int i = 0; i < COLOR_COUNT; i++) {
		colors[i] = randColor(i);
	}
	return colors;
}

static inline bool same_color(Color a, Color b) {
	return fabsf(a.r - b.r) < 0.01f &&
	       fabsf(a.b - b.b) < 0.01f &&
	       fabsf(a.g - b.g) < 0.01f;
}
