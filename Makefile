SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -g
TARGET=main

OBJ=main.o interpolation.o

.PHONY=all
all: $(TARGET)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY=clean
clean:
	rm *.o
	rm $(TARGET)