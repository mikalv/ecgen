####
#
# ecgen, tool for generating Elliptic curve domain parameters
# Copyright (C) 2017 J08nY
#
####

CC ?= gcc

CFLAGS = -Wall
DEBUG ?= 0
TEST ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -g -Werror -pedantic
else ifeq ($(TEST), 1)
	CFLAGS += --coverage -g -O0
else
	CFLAGS += -DNDEBUG -O3
endif
LDFLAGS = -L../lib/parson -L../lib/sha1 -L../lib/pari

INCLUDES = -I. -I../lib
LIBS = -lrt -lpari -lpthread -lparson -lsha1

####

ECGEN_SRC = ecgen.c $(wildcard */*.c)
ECGEN_OBJ = $(patsubst %.c,%.o, $(ECGEN_SRC))

ECONVERT_SRC = econvert.c
ECONVERT_OBJ = $(patsubst %.c,%.o, $(ECONVERT_SRC))

SRC = $(wildcard *.c) $(wildcard */*.c)
HDR = $(wildcard */*.h)

####

all: ecgen econvert

ecgen: ecgen.o $(ECGEN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)
	mv ecgen ..

econvert: econvert.o $(ECONVERT_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)
	mv econvert ..

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

####

clean-all: clean clean-cov
	rm -f ../ecgen
	rm -f ../econvert

clean:
	find . -type f -name '*.o' -exec rm {} +

clean-cov:
	find . -type f -name '*.gcda' -exec rm {} +
	find . -type f -name '*.gcno' -exec rm {} +
	find . -type f -name '*.gcov' -exec rm {} +

format:
	clang-format -i $(SRC)
	clang-format -i $(HDR)

.PHONY: all clean-all clean format
