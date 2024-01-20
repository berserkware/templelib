#include <SDL2/SDL.h>
#include "window.h"
#include "templelib.h"
#include "colors.h"
#include "glyphs.h"
#include "gr.h"
#include "window_draw.h"

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

void draw_close_button(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);
  
  set_color(app, WHITE);
  draw_glyph_on_grid(app, SOLID_BLOCK, gw-2, 0);
  draw_glyph_on_grid(app, SOLID_BLOCK, gw-3, 0);
  draw_glyph_on_grid(app, SOLID_BLOCK, gw-4, 0);

  set_color(app,BLUE);
  draw_glyph_on_grid(app, 60, gw-2, 0);
  draw_glyph_on_grid(app, 55, gw-3, 0);
  draw_glyph_on_grid(app, 58, gw-4, 0);
}

// draws the window border and decorations
void draw_window_decorations(TempleApp* app) {
  draw_window_border(app);
  draw_close_button(app);
}
