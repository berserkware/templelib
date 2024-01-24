#ifndef GR_H
#define GR_H

#include "templelib.h"

// draws a glyph at a grid postion.
void draw_glyph_on_grid(TempleApp* app, int gi, int gx, int gy);

void draw_glyph_sentence(TempleApp* app, char* sentence, int length, int x, int y);

void draw_glyph(TempleApp* app, int gi, int x, int y);

#endif
