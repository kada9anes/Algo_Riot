CC = gcc
CFLAGS = -Wall -Wextra -I./library
LDFLAGS = -lm

SRC := $(shell find . -type f -name "*.c")
TARGET = mian

all: $(TARGET)

$(TARGET):
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o
