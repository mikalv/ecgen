/*
 * ecgen, tool for generating Elliptic curve domain parameters
 * Copyright (C) 2017 J08nY
 */
#include "equation.h"
#include "io/input.h"

int a_random(curve_t *curve, config_t *config, arg_t *args) {
	curve->a = genrand(curve->field);
	return 1;
}

int a_input(curve_t *curve, config_t *config, arg_t *args) {
	pari_sp ltop = avma;
	GEN inp = input_int("a:", config->bits);
	if (gequalm1(inp)) {
		avma = ltop;
		return 0;
	}
	curve->a = gerepilecopy(ltop, inp);
	// TODO change a to a field element here?. a t_INTMOD or a t_FFELT.
	return 1;
}

static GEN a = NULL;

int a_once(curve_t *curve, config_t *config, arg_t *args) {
	if (a) {
		curve->a = gcopy(a);
		return 1;
	}

	int inp = a_input(curve, config, args);
	if (inp) {
		a = gclone(curve->a);
	} else {
		return 0;
	}
	return 1;
}

int a_zero(curve_t *curve, config_t *config, arg_t *args) {
	curve->a = gen_0;
	return 1;
}

int a_one(curve_t *curve, config_t *config, arg_t *args) {
	curve->a = gen_1;
	return 1;
}

int a_seed(curve_t *curve, config_t *config, arg_t *args) {
	// TODO implement
	return INT_MIN;
}

int b_random(curve_t *curve, config_t *config, arg_t *args) {
	curve->b = genrand(curve->field);
	return 1;
}

int b_input(curve_t *curve, config_t *config, arg_t *args) {
	pari_sp ltop = avma;
	GEN inp = input_int("b:", config->bits);
	if (gequalm1(inp)) {
		avma = ltop;
		return 0;
	}
	curve->b = gerepilecopy(ltop, inp);
	// TODO change b to a field element here?. a t_INTMOD or a t_FFELT.
	return 1;
}

static GEN b = NULL;

int b_once(curve_t *curve, config_t *config, arg_t *args) {
	if (b) {
		curve->b = gcopy(b);
		return 1;
	}

	int inp = b_input(curve, config, args);
	if (inp) {
		b = gclone(curve->b);
	} else {
		return 0;
	}
	return 1;
}

int b_zero(curve_t *curve, config_t *config, arg_t *args) {
	curve->b = gen_0;
	return 1;
}

int b_one(curve_t *curve, config_t *config, arg_t *args) {
	curve->b = gen_1;
	return 1;
}

int b_seed(curve_t *curve, config_t *config, arg_t *args) {
	// TODO implement
	return INT_MIN;
}