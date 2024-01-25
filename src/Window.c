#include <SDL2/SDL.h>
#include "Window.h"
#include "App.h"
#include "Gr/GrColors.h"
#include "Gr/GrGlyphs.h"
#include "Gr/Gr.h"

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

// Aligns the window size to the glyph size
void AlignSizeToGlyphs(TempleApp* app) {
  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);
  
  if (w % app->real_glyph_size != 0) {
    SDL_SetWindowSize(app->window, w-(w % app->real_glyph_size), h);
  }
  if (h % app->real_glyph_size != 0) {
    SDL_SetWindowSize(app->window, w, h-(h % app->real_glyph_size));
  }
}

// Aligns the window postion to the global glyph grid
void AlignPosToGrid(TempleApp* app) {
  int x, y;
  SDL_GetWindowPosition(app->window, &x, &y);
  
  if (x % app->real_glyph_size != 0) {
    SDL_SetWindowPosition(app->window, x+(x % app->real_glyph_size), y);
  }

  if (y % app->real_glyph_size != 0) {
    SDL_SetWindowPosition(app->window, x, y+(y % app->real_glyph_size));
  }
}

// Updates the window's postion and size.
void UpdateWindow(TempleApp* app) {
  AlignSizeToGlyphs(app);
  AlignPosToGrid(app);
}
