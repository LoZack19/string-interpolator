# Set the shell to use
SHELL=/bin/bash

# Set the C compiler to use
CC=gcc

# Set the C flags to use
CFLAGS=-Wall -Wextra -g -I./ -std=c11

# Set the target executable name
TARGET=main

# Set the object files to compile
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o) main.o

# Default target
.PHONY: all
all: $(TARGET)

# Compile C files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Clean target
.PHONY: clean
clean:
	rm -f *.o src/*.o
	rm -f $(TARGET)

# Optional: add a target to run the program
.PHONY: run
run: $(TARGET)
	./$(TARGET)
