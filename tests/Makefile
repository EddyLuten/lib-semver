CC = clang
FLAGS = -Wall -Wextra -Werror --std=c99 -O0 -DDEBUG -g
INCLUDE_DIR = ../include

all: dirs build/custom-allocators build/simple-parse build/compare build/create build/create-meta build/to-string

dirs:
	@mkdir -p ./build

clean:
	@rm -rf ./build

build/semver.o: ../source/semver.c
	$(CC) $(FLAGS) -c ../source/semver.c -o build/semver.o -I$(INCLUDE_DIR)

build/custom-allocators.o: custom-allocators.c
	$(CC) $(FLAGS) -c custom-allocators.c -o build/custom-allocators.o -I$(INCLUDE_DIR)

build/simple-parse.o: simple-parse.c
	$(CC) $(FLAGS) -c simple-parse.c -o build/simple-parse.o -I$(INCLUDE_DIR)

build/compare.o: compare.c
	$(CC) $(FLAGS) -c compare.c -o build/compare.o -I$(INCLUDE_DIR)

build/create.o: create.c
	$(CC) $(FLAGS) -c create.c -o build/create.o -I$(INCLUDE_DIR)

build/create-meta.o: create-meta.c
	$(CC) $(FLAGS) -c create-meta.c -o build/create-meta.o -I$(INCLUDE_DIR)

build/to-string.o: to-string.c
	$(CC) $(FLAGS) -c to-string.c -o build/to-string.o -I$(INCLUDE_DIR)

build/custom-allocators: build/semver.o build/custom-allocators.o
	$(CC) $(FLAGS) -o build/custom-allocators build/semver.o build/custom-allocators.o

build/simple-parse: build/semver.o build/simple-parse.o
	$(CC) $(FLAGS) -o build/simple-parse build/semver.o build/simple-parse.o

build/compare: build/semver.o build/compare.o
	$(CC) $(FLAGS) -o build/compare build/semver.o build/compare.o

build/create: build/semver.o build/create.o
	$(CC) $(FLAGS) -o build/create build/semver.o build/create.o

build/create-meta: build/semver.o build/create-meta.o
	$(CC) $(FLAGS) -o build/create-meta build/semver.o build/create-meta.o

build/to-string: build/semver.o build/to-string.o
	$(CC) $(FLAGS) -o build/to-string build/semver.o build/to-string.o

.PHONY: all clean dirs
