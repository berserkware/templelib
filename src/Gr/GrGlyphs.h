#ifndef GLYPHS_H
#define GLYPHS_H

#include <SDL2/SDL.h>
#include "../App.h"

// Defines the index of the border glyphs
#define SOLID_BLOCK 219-32

#define BOX_DOUBLE_VERTICAL 205-32
#define BOX_DOUBLE_TOP_RIGHT 187-32
#define BOX_DOUBLE_BOTTOM_RIGHT 188-32
#define BOX_DOUBLE_BOTTOM_LEFT 200-32
#define BOX_DOUBLE_TOP_LEFT 201-32
#define BOX_DOUBLE_HORIZONTAL 186-32

#define BOX_SINGLE_VERTICAL 196-32
#define BOX_SINGLE_TOP_RIGHT 191-32
#define BOX_SINGLE_BOTTOM_LEFT 192-32
#define BOX_SINGLE_BOTTOM_RIGHT 217-32
#define BOX_SINGLE_TOP_LEFT 218-32
#define BOX_SINGLE_HORIZONTAL 179-32

extern SDL_Texture* glyphs_texture;

extern SDL_Rect* glyphs;

// Loads the glyph texture, and calculates the rects.
void LoadGlyphs();

// Frees the glyph textures and rects.
void FreeGlyphs();

// Takes an ascii char and get the corrosponding glyph.
int CharToGlyphIndex(char c);

// draws a glyph at a grid postion.
void DrawGlyphOnGrid(TempleApp* app, int gi, int gx, int gy);

void DrawGlyphSentence(TempleApp* app, char* sentence, int length, int x, int y);

void DrawGlyph(TempleApp* app, int gi, int x, int y);

#endif
