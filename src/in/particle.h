/* particle.h */

#pragma once

#include "util.h"
#include <GL/gl.h>
#include <math.h>

#define PART_COUNT 5


typedef struct {
	float x, y;
	float vx, vy;
	float radius;
	Color color;
	float ax, ay;
	float mass;
	float fx, fy;
	Vec2D prev;
} Particle_2D;

void init_Particles_2D();

void update_Particles_2D(float dt);

void render_Particles_2D();

void move_particle(Particle_2D *p, float dt);

void draw_Particle_2D(Particle_2D *p);

void reset();

void handle_bounds(Particle_2D *p, float dt);

void apply_rule_matrix(Particle_2D *p, Particle_2D *particles, float range);
