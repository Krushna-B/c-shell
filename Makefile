CC := clang
CFlags := -std=c11 -Wall -Wextra -Wpedantic -O0 -g
INCLUDE := -Iinclude

TARGET := build/lsh
SRCS    := $(wildcard src/*.c)
OBJS    := $(patsubst src/%.c,build/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p build
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build