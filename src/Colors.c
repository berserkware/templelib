#include <SDL2/SDL.h>
#include "App.h"
#include "Colors.h"
#include "Glyphs.h"

void SetColor(TempleApp* app, Color color) {
  SDL_SetRenderDrawColor(app->renderer, color.r, color.g, color.b, 255);
  SDL_SetTextureColorMod(glyphs_texture, color.r, color.g, color.b);
}
