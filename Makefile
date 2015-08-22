CC = g++
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
CFLAGS = -O3 -std=c++11 -Wall -Wextra -pedantic

OUTPUT = sdlgl
LIBS = -lSDL2 -lGL
INCL_DIRS = -I./src -I./src/libla

$(OUTPUT): build $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTPUT) $(LIBS) $(CFLAGS)

build/%.o: src/%.cpp
	$(CC) -c $< -o $@ $(INCL_DIRS) $(CFLAGS)

build:
	@mkdir -p build

clean:
	@rm -fr build $(OUTPUT)
