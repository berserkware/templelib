#include <string.h>
#include <SDL2/SDL.h>
#include "app.h"
#include "glyphs.h"
#include "colors.h"

void draw_glyph(TempleApp* app, int gi, int x, int y) {
  SDL_Rect dstrect = {x,y, app->real_glyph_size, app->real_glyph_size};
  SDL_RenderCopy(app->renderer, glyphs_texture, &glyphs[gi], &dstrect);
}

void draw_glyph_on_grid(TempleApp* app, int gi, int gx, int gy) {
  // the actual position on the window
  int x, y;
  x = gx * app->real_glyph_size;
  y = gy * app->real_glyph_size;
  
  draw_glyph(app, gi, x, y);
}

void draw_glyph_sentence(TempleApp* app, char* sentence, int length, int x, int y) {
  for (int i = 0; i<length; i++) {
    if (sentence[i] == ' ')
      continue;
    draw_glyph(app, char_to_glyph_index(sentence[i]), x+(app->real_glyph_size*i), y);
  }
}
