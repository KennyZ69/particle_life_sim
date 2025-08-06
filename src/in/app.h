/* app.h */

#pragma once

#include "util.h"

// Initialize the application screen and processes
bool init(const char *title);

// Run the core application loop
void run_2D();
void run_3D();

void cleanup();
