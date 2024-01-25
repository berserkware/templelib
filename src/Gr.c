#include <string.h>
#include <SDL2/SDL.h>
#include "App.h"
#include "Glyphs.h"
#include "Colors.h"

void DrawGlyph(TempleApp* app, int gi, int x, int y) {
  SDL_Rect dstrect = {x,y, app->real_glyph_size, app->real_glyph_size};
  SDL_RenderCopy(app->renderer, glyphs_texture, &glyphs[gi], &dstrect);
}

void DrawGlyphOnGrid(TempleApp* app, int gi, int gx, int gy) {
  // the actual position on the window
  int x, y;
  x = gx * app->real_glyph_size;
  y = gy * app->real_glyph_size;
  
  DrawGlyph(app, gi, x, y);
}

void DrawGlyphSentence(TempleApp* app, char* sentence, int length, int x, int y) {
  for (int i = 0; i<length; i++) {
    if (sentence[i] == ' ')
      continue;
    DrawGlyph(app, CharToGlyphIndex(sentence[i]), x+(app->real_glyph_size*i), y);
  }
}
