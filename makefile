CC = gcc
CFLAGS = -Wall -Wextra -lm

# Automatically find all C files everywhere
SRC := $(shell find . -type f -name "*.c")

TARGET = mian

all: $(TARGET)

$(TARGET):
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET) *.o
