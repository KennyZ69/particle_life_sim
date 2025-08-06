/* main.c */

#include "src/in/app.h"

int main(void) {
	if(!init("LifeSim")) {
		return 1;
	}

	run_2D();

	cleanup();

	printf("Exiting sim...\n");
	return 0;
}
