# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 $(shell pkg-config --cflags opencv3)
LDFLAGS = $(shell pkg-config --libs opencv3)

# Target executable
TARGET := GifMaker

SRCS := src/*.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)
