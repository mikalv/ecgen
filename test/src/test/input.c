/*
 * ecgen, tool for generating Elliptic curve domain parameters
 * Copyright (C) 2017 J08nY
 */
#include "input.h"
#include "io/input.h"

FILE *write_in;

void input_setup(void) {
	config_t cfg;
	memset(&cfg, 0, sizeof(cfg));
	input_init(&cfg);

	int in_fd[2];
	pipe(in_fd);

	write_in = fdopen(in_fd[1], "w");
	setlinebuf(write_in);
	in = fdopen(in_fd[0], "r");
	setlinebuf(in);
}

void input_teardown(void) {
	input_quit();
	fclose(write_in);
}