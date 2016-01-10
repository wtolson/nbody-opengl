CC=clang

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -std=gnu99 -Wall -Werror -Wno-unused -g
LFLAGS = -lSDL2 -lSDL2_mixer -lSDL2_net -g


nbody: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o nbody

valgrind: nbody
	valgrind ./nbody

clean:
	rm -f $(OBJ)
	rm -f nbody


.PHONEY: valgrind clean
