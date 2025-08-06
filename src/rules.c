/* rules.c */

#include "in/rules.h"
#include "in/particle.h"
#include "in/util.h"
#include <stdio.h>

void apply_force(Particle_2D *p, Vec2D force) {
	Vec2D acc = Vec2D_mult(force, 1.0f / p->mass);
	p->ax += acc.x;
	p->ay += acc.y;
}

void attract_color_simple(Particle_2D *p, Particle_2D *particles, float range) {
	float fx = 0, fy = 0;
	float damp =  0.5, g = -0.1;

	for (int i = 0; i < PART_COUNT; i++) {
		Particle_2D *p2 = &particles[i];
		// if (p2 == p || same_color(p2->color, p->color)) continue;
		if (p2 == p || !same_color(p2->color, p->color)) continue;

		float dx = p2->x - p->x;
		float dy = p2->y - p->y;

		float dist = sqrtf(dx*dx + dy*dy);
		if (dist > 0 && dist < range) {
			float F = g * 1/dist;
			fx += (F * dx);
			fy += (F * dy);
			// printf("Applying force x = %.3f; y = %.3f...\n", fx, fy);
		}
		}
	p->vx = (p->vx + fx) * damp;
	p->vy = (p->vy + fy) * damp;

	p->x += p->vx;
	p->y += p->vy;
}

void attract_color(Particle_2D *p, Particle_2D *particles, float range) {
        for (int i = 0; i < PART_COUNT; i++) {
		Particle_2D *p2 = &particles[i];
		if (p2 == p) continue;
		if (!same_color(p->color, p2->color)) continue;

		float dx = p2->x - p->x;
		float dy = p2->y - p->y;
		float dist_sq = dx*dx + dy*dy;

		if (dist_sq <= 0) continue;
		float dist = sqrtf(dist_sq);
		if (dist > range) continue;

		float force = (GRAVITY * p->mass * p2->mass) / dist_sq;

		printf("Adding force: %.3f...x = %.2f; y = %.2f\n", force, force*dx/dist, force*dy/dist);

		p->fx += force * dx / dist;
		p->fy += force * dy / dist;

	}
}

void bounce_on_collision(Particle_2D *p, Particle_2D *particles) {
	for (int i = 0; i < PART_COUNT; i++) {
		if (&particles[i] == p) continue;

		float dx = particles[i].x - p->x;
		float dy = particles[i].y - p->y;
		float dist_sq = dx*dx + dy*dy;
		float rads = particles[i].radius + p->radius;

		if (dist_sq < rads * rads) {
			float dist = sqrtf(dist_sq);
			float overlap = rads - dist;
			float nx = dx / dist;
			float ny = dy / dist;
			float rel_vx = particles[i].vx - p->vx;
			float rel_vy = particles[i].vy - p->vy;
			float rel_vel = rel_vx * nx + rel_vy * ny;
			if (rel_vel < 0) {
				float impulse = 2 * rel_vel / (particles[i].mass + p->mass);
				particles[i].vx -= impulse * p->mass * nx;
				particles[i].vy -= impulse * p->mass * ny;
				p->vx += impulse * particles[i].mass * nx;
				p->vy += impulse * particles[i].mass * ny;
				p->x -= overlap * nx * 0.5f;
				p->y -= overlap * ny * 0.5f;
				particles[i].x += overlap * nx * 0.5f;
				particles[i].y += overlap * ny * 0.5f;
				p->ax = particles[i].ax = 0.0f;
				p->ay = particles[i].ay = 0.0f;
			}
		}
	}
}
