CC = gcc

CFLAGS = -Wall

SRC := $(wildcard src/*.c)
EXE = bin/templelib

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -f $(EXE)

.PHONY: all clean
