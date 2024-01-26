#include <SDL2/SDL.h>
#include "Win.h"
#include "App.h"
#include "Gr/GrColors.h"
#include "Gr/GrGlyphs.h"

// Gets the window grid size by dividing the window width by the
// scaled glyph size
void GetWindowGridSize(TempleApp* app, int* gw, int* gh) {
  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);

  *gw = w / app->real_glyph_size;
  *gh = h / app->real_glyph_size;
}

void GetWindowGridPosition(TempleApp* app, int* gx, int* gy) {
  int x, y;
  SDL_GetWindowPosition(app->window, &x, &y);

  *gx = x / app->real_glyph_size;
  *gy = y / app->real_glyph_size;
}

void WinBorder(TempleApp* app) {
  
  if (app->window_flags & WINDOWf_NO_BORDER) {
    app->window_flags &= ~WINDOWf_NO_BORDER;
  } else {
    app->window_flags |= WINDOWf_NO_BORDER;
  }
}
