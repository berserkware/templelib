#include <SDL2/SDL.h>
#include "window.h"
#include "templelib.h"
#include "colors.h"
#include "glyphs.h"
#include "gr.h"

// Gets the window grid size by dividing the window width by the
// scaled glyph size
void get_window_grid_size(TempleApp* app, int* gw, int* gh) {
  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);

  *gw = w / app->real_glyph_size;
  *gh = h / app->real_glyph_size;
}

// Updates the window's postion and size.
void update_window(TempleApp* app) {

  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);
  
  // Makes sure window width and height is alligned with spritet size
  if (w % app->real_glyph_size != 0) {
    SDL_SetWindowSize(app->window, w-(w % app->real_glyph_size), h);
  }
  if (h % app->real_glyph_size != 0) {
    SDL_SetWindowSize(app->window, w, h-(h % app->real_glyph_size));
  }
}

// draws the border of the window
void draw_window_border(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  set_color(app, BLUE);

  // draws the corners
  draw_glyph_on_grid(app, BORDER_TOP_LEFT_CORNER, 0, 0);
  draw_glyph_on_grid(app, BORDER_TOP_RIGHT_CORNER, gw-1, 0);
  draw_glyph_on_grid(app, BORDER_BOTTOM_LEFT_CORNER, 0, gh-1);
  draw_glyph_on_grid(app, BORDER_BOTTOM_RIGHT_CORNER, gw-1, gh-1);

  // draws the columns
  int r;
  for (r = 1; r<gh-1; r++) {
     draw_glyph_on_grid(app, BORDER_COLUMN_LEFT, 0, r);
  }
  for (r = 1; r<gh-1; r++) {
     draw_glyph_on_grid(app, BORDER_COLUMN_RIGHT, gw-1, r);
  }

  // draws the rows
  int c;
  for (c = 1; c<gw-1; c++) {
     draw_glyph_on_grid(app, BORDER_ROW_TOP, c, 0);
  }
  for (c = 1; c<gw-1; c++) {
     draw_glyph_on_grid(app, BORDER_ROW_BOTTOM, c, gh-1);
  }
}

// draws the window border and decorations
void draw_window_decorations(TempleApp* app) {
  draw_window_border(app);
}
