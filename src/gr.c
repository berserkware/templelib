#include <SDL2/SDL.h>
#include "colors.h"
#include "templelib.h"
#include "glyphs.h"

void draw_glyph_on_grid(TempleApp* app, int gi, int gx, int gy) {
  // the actual position on the window
  int x, y;
  x = gx * app->real_glyph_size;
  y = gy * app->real_glyph_size;
  
  SDL_Rect dstrect = {x,y, app->real_glyph_size, app->real_glyph_size};
  SDL_RenderCopy(app->renderer, glyphs_texture, &glyphs[gi], &dstrect);
}
