CC=clang

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -std=gnu99 -Wall -Werror -Wno-unused -g
LFLAGS = -lSDL2 -framework OpenGL -g


nbody: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o nbody

$(OBJECTS): $(HEADERS)

valgrind: nbody
	valgrind ./nbody

clean:
	rm -rf *.dSYM
	rm -f $(OBJECTS)
	rm -f nbody


.PHONEY: valgrind clean
