#include <SDL2/SDL.h>
#include "templelib.h"
#include "colors.h"
#include "glyphs.h"

void set_color(TempleApp* app, Color color) {
  SDL_SetRenderDrawColor(app->renderer, color.r, color.g, color.b, 255);
  SDL_SetTextureColorMod(glyphs_texture, color.r, color.g, color.b);
}
