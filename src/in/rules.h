/* rules.h */

#pragma once

#include "particle.h"

void apply_force(Particle_2D *p, Vec2D force);

// void bounce_on_collision(Particle_2D *p);

void bounce_on_collision(Particle_2D *p, Particle_2D *particles);

void attract_color(Particle_2D *p, Particle_2D *particles, float range);

void attract_color_simple(Particle_2D *p, Particle_2D *particles, float range);
