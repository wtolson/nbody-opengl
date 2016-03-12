CXX=clang++

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cc)
OBJECTS = $(SOURCES:.cc=.o)

CXXFLAGS = -march=native -O2
# CXXFLAGS += -Wall -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing
# CXXFLAGS += -Wno-unused-parameter -Wno-gnu-zero-variadic-macro-arguments

LFLAGS = -lSDL2 -framework OpenGL


all: nbody

debug: CFLAGS += -DNDEBUG -g
debug: LFLAGS += -g
debug: nbody

nbody: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LFLAGS) -o nbody

$(OBJECTS): $(HEADERS)

valgrind: nbody
	valgrind ./nbody

clean:
	rm -rf *.dSYM
	rm -f $(OBJECTS)
	rm -f nbody


.PHONEY: all debug valgrind clean
