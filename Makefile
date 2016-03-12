CC=clang

HEADERS = $(wildcard src/*.h) $(wildcard src/**/*.h)
SOURCES = $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -std=gnu99 -march=native -O2 -I src
CFLAGS += -Wall -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing
CFLAGS += -Wno-unused-parameter -Wno-gnu-zero-variadic-macro-arguments

LFLAGS = -lm -lSDL2 -framework OpenGL


all: nbody

debug: CFLAGS += -DNDEBUG -g
debug: LFLAGS += -g
debug: nbody

nbody: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o nbody

$(OBJECTS): $(HEADERS)

valgrind: nbody
	valgrind ./nbody

clean:
	rm -rf *.dSYM
	rm -f $(OBJECTS)
	rm -f nbody


.PHONEY: all debug valgrind clean
