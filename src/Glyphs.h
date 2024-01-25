#ifndef GLYPHS_H
#define GLYPHS_H

#include <SDL2/SDL.h>

// Defines the index of the border glyphs
#define BORDER_COLUMN_LEFT 94
#define BORDER_COLUMN_RIGHT 95
#define BORDER_TOP_LEFT_CORNER 96
#define BORDER_TOP_RIGHT_CORNER 97
#define BORDER_BOTTOM_LEFT_CORNER 98
#define BORDER_BOTTOM_RIGHT_CORNER 99
#define BORDER_ROW_TOP 100
#define BORDER_ROW_BOTTOM 101
#define SOLID_BLOCK 102
#define SMALL_BORDER_COLUMN_LEFT 103
#define SMALL_BORDER_COLUMN_RIGHT 104
#define SMALL_BORDER_TOP_LEFT_CORNER 105
#define SMALL_BORDER_TOP_RIGHT_CORNER 106
#define SMALL_BORDER_BOTTOM_LEFT_CORNER 107
#define SMALL_BORDER_BOTTOM_RIGHT_CORNER 108
#define SMALL_BORDER_ROW_TOP 109
#define SMALL_BORDER_ROW_BOTTOM 110

extern SDL_Texture* glyphs_texture;

extern SDL_Rect* glyphs;

// Loads the glyph texture, and calculates the rects.
void LoadGlyphs();

// Frees the glyph textures and rects.
void FreeGlyphs();

// Takes an ascii char and get the corrosponding glyph.
int CharToGlyphIndex(char c);

#endif
