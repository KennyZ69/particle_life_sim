/* particle.c */

#include "in/particle.h"
#include "in/rules.h"
#include "in/util.h"
#include <GL/gl.h>

static Particle_2D particles[PART_COUNT];

void init_Particles_2D() {
	srand(time(NULL));
	Color *colors = init_colors();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-BOUNDS, BOUNDS, -BOUNDS, BOUNDS, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < PART_COUNT; i++) {
		particles[i].x = randf(-5.0f, 5.0f);
		particles[i].y = randf(-5.0f, 5.0f);
		particles[i].radius = randf(0.2f, 0.25f);
		particles[i].mass = particles[i].radius * particles[i].radius * M_PI; // Assuming mass is proportional to area
		particles[i].color = colors[rand() % COLOR_COUNT];
		if (particles[i].color.idx == 1) {
			particles[i].vx = 0;
			particles[i].vy = 0;
		} else {
		particles[i].vx = randf(-0.50f, 0.50f);
		particles[i].vy = randf(-0.50f, 0.50f);
		}
		// particles[i].vx = 0;
		// particles[i].vy = 0;
		// particles[i].color = colors[0];
		particles[i].prev = (Vec2D){particles[i].x-particles[i].vx*DELTA, particles[i].y-particles[i].vy*DELTA};
		particles[i].ax = 0.0f;
		particles[i].ay = 0.0f;
		particles[i].fx = 0;
		particles[i].fy = 0;
	}
}

void move_particle(Particle_2D *p, float dt) {
	p->ax = p->fx / p->mass * ENERGY_LOSS;
	p->ay = p->fy / p->mass * ENERGY_LOSS;
	// p->ax = p->fx / p->mass;
	// p->ay = p->fy / p->mass;

	Vec2D pos = {p->x, p->y};
	
	// verlet
	p->x += (p->x - p->prev.x) + p->ax * dt * dt;
	p->y += (p->y - p->prev.y) + p->ay * dt * dt;

	p->vx = (pos.x - p->prev.x) / dt; // optionally also / dt
	p->vy = (pos.y - p->prev.y) / dt;

	p->prev.x = pos.x;
	p->prev.y = pos.y;

	p->fx = 0;
	p->fy = 0;
}

void update_Particles_2D(float dt) {
	for (int i = 0; i < PART_COUNT; i++) {

		// apply_rule_matrix(&particles[i], particles, 5);
		// attract_color(&particles[i], particles, 2.0f);
		// move_particle(&particles[i], dt);
		// attract_color_simple(&particles[i], particles, 4.0f);
		// handle_bounds(&particles[i], dt);
		apply_rules_simple(&particles[i], particles, 5);
	}
}

void handle_bounds(Particle_2D *p, float dt) {
	if (p->x - p->radius < -BOUNDS) { 
		p->x = -BOUNDS + p->radius;
		p->prev.x = p->x + p->vx * dt;
		p->vx *= -1;
	} else if (p->x + p->radius > BOUNDS) {
		p->x = BOUNDS - p->radius;
		p->prev.x = p->x + p->vx * dt;
		p->vx *= -1;
	}
	if (p->y - p->radius < -BOUNDS) { 
		p->y = -BOUNDS + p->radius;
		p->prev.y = p->y + p->vy * dt;
		p->vy *= -1;
	} else if (p->y + p->radius > BOUNDS) {
		p->y = BOUNDS - p->radius;
		p->prev.y = p->y + p->vy * dt;
		p->vy *= -1;
	}
}

void render_Particles_2D() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawBounds();
	for (int i = 0; i < PART_COUNT; i++) {
		draw_Particle_2D(&particles[i]);
	}
	glEnd();
}



void draw_Particle_2D(Particle_2D *p) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(p->color.r, p->color.g, p->color.b);
	glVertex2f(p->x, p->y);
	for (int i = 0; i <= PART_SEGMENTS; i++) {
		float angle = 2.0f * M_PI * i / PART_SEGMENTS;
		float dx = p->radius * cosf(angle);
		float dy = p->radius * sinf(angle);
		glVertex2f(p->x + dx, p->y + dy);
	}
	glEnd();
}

void reset() {
	init_Particles_2D();
}
