#ifndef GR_H
#define GR_H

#include "../App.h"

// draws a glyph at a grid postion.
void DrawGlyphOnGrid(TempleApp* app, int gi, int gx, int gy);

void DrawGlyphSentence(TempleApp* app, char* sentence, int length, int x, int y);

void DrawGlyph(TempleApp* app, int gi, int x, int y);

#endif
