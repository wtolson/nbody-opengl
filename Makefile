CC=clang

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -std=gnu99 -march=native -O2
CFLAGS += -Wall -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing
CFLAGS += -Wno-unused-parameter -Wno-gnu-zero-variadic-macro-arguments

LFLAGS = -lSDL2 -framework OpenGL


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
