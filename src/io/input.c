/*
 * ecgen, tool for generating Elliptic curve domain parameters
 * Copyright (C) 2017 J08nY
 */
#define _POSIX_C_SOURCE 200809L
#include "input.h"
#include <parson/parson.h>
#include "output.h"

FILE *in;
int delim;

static GEN input_i(const char *prompt, long bits) {
	if (prompt && in == stdin) {
		fprintf(out, "%s ", prompt);
	}
	char *line = NULL;
	size_t n = 0;

	ssize_t len = getdelim(&line, &n, delim, in);
	if (len <= 0) {
		return gen_m1;
	}
	if (len == 1 && !feof(in)) {
		free(line);
		return gen_m1;
	}
	for (size_t i = 0, j = 0; (line[j] = line[i]); j += !isspace(line[i++]))
		;

	if (len <= 3 || !(line[0] == '0' && (line[1] == 'x' || line[1] == 'X'))) {
		char *new_line = realloc(line, (size_t)(len + 2));
		if (!new_line) {
			perror("Couldn't alloc.");
			exit(1);
		}
		memmove(new_line + 2, new_line, (size_t)len);
		new_line[0] = '0';
		new_line[1] = 'x';
		if (!feof(in)) {
			new_line[len + 1] = 0;
		} else {
			new_line[len + 2] = 0;
		}
		line = new_line;
	}

	pari_sp ltop = avma;
	GEN in = strtoi(line);
	free(line);

	// check bitsize here
	GEN size = int2n(bits);
	if (cmpii(in, size) <= 0) {
		return gerepileupto(ltop, in);
	} else {
		fprintf(stderr, "Number too big(> %ld bits).\n", bits);
		return gen_m1;
	}
}

GEN input_prime(const char *prompt, long bits) {
	GEN read = input_i(prompt, bits);
	if (equalii(read, gen_m1)) {
		return read;
	} else {
		if (isprime(read)) {
			return read;
		} else {
			fprintf(stderr, "Number is not prime. Prime required.\n");
			return gen_m1;
		}
	}
}

GEN input_int(const char *prompt, long bits) { return input_i(prompt, bits); }

GEN input_short(const char *prompt) { return input_i(prompt, 16); }

GEN input_string(const char *prompt) {
	if (prompt && in == stdin) {
		fprintf(out, "%s ", prompt);
	}
	char *line = NULL;
	size_t n = 0;

	ssize_t len = getdelim(&line, &n, delim, in);
	if (len == 1) {
		free(line);
		return strtoGENstr("");
	}

	line[len - 1] = 0;
	GEN result = strtoGENstr(line);
	free(line);
	return result;
}

GEN input_param(param_t param, const char *prompt, long bits) {
	switch (param) {
		case PARAM_PRIME:
			return input_prime(prompt, bits);
		case PARAM_INT:
			return input_int(prompt, bits);
		case PARAM_SHORT:
			return input_short(prompt);
		case PARAM_STRING:
			return input_string(prompt);
	}
	return gen_m1;
}

void input_init(config_t *cfg) {
	json_set_allocation_functions(pari_malloc, pari_free);

	if (cfg->input) {
		in = fopen(cfg->input, "r");
		delim = ',';
		if (!in) {
			perror("Failed to open input file.");
			exit(1);
		}
	} else {
		in = stdin;
		delim = '\n';
	}
}

void input_quit(void) {
	if (in != NULL && in != stdout) {
		fclose(in);
	}
}
