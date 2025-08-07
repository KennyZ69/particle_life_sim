/* rules.h */

#pragma once

#include "particle.h"
#include "util.h"

static float Rule_Matrix[COLOR_COUNT][COLOR_COUNT] = {
	{-0.1, 0.1},
	{0.1, 0}
	// {0, 1, 1, -1, 0},
	// {1, 0, 0, 0, 0},
	// {1, 0, 0, 0, 0},
	// {-1, 0, 0, 0, 0},
	// {0, 0, 0, 0, 0}
};

void apply_force(Particle_2D *p, Vec2D force);

// void bounce_on_collision(Particle_2D *p);

void bounce_on_collision(Particle_2D *p, Particle_2D *particles);

void attract_color(Particle_2D *p, Particle_2D *particles, float range);

void attract_color_simple(Particle_2D *p, Particle_2D *particles, float range);

void apply_rules_simple(Particle_2D *p, Particle_2D *particles, float range);
