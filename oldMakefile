CC = gcc

# Defines the stuff for the glyphsheet. To compile for platforms other than linux, you
# will have to change this stuff.
DATA_DIR = ~/.templelib
GLYPH_SIZE = 8
GLYPHSHEET_FILE = glyphsheet.png
GLYPHSHEET_SOURCE = data/glyphsheet.png
GLYPHSHEET_PATH = $(shell readlink -f $(DATA_DIR)/$(GLYPHSHEET_FILE))

CFLAGS = -Wall -DGLYPH_SIZE=$(GLYPH_SIZE) -DGLYPHSHEET_PATH="\"$(GLYPHSHEET_PATH)\""
LDFLAGS = -lSDL2 -lSDL2_image

SRC := $(wildcard src/*.c)
EXE = bin/templelib

target: $(DATA_DIR)/$(GLYPHSHEET_FILE) $(EXE)

$(DATA_DIR)/$(GLYPHSHEET_FILE): $(GLYPHSHEET_SOURCE)
	mkdir $(DATA_DIR) -p
	cp $(GLYPHSHEET_SOURCE) $(DATA_DIR)/$(GLYPHSHEET_FILE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) $(LDFLAGS)

clean:
	rm -f $(EXE)
	rm -f $(DATA_DIR)/$(GLYPHSHEET_FILE)
	rmdir $(DATA_DIR)

.PHONY: all clean
