#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "app.h"
#include "colors.h"
#include "glyphs.h"
#include "gr.h"
#include "window_draw.h"

// draws the border of the window
void draw_window_border(TempleApp* app, int in_focus) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  set_color(app, WHITE);
  draw_glyph_on_grid(app, SOLID_BLOCK, 0, 0);
  draw_glyph_on_grid(app, SOLID_BLOCK, gw-1, 0);
  draw_glyph_on_grid(app, SOLID_BLOCK, 0, gh-1);
  draw_glyph_on_grid(app, SOLID_BLOCK, gw-1, gh-1);

  set_color(app, BLUE);
  // draws the corners
  if (in_focus) {
    draw_glyph_on_grid(app, BORDER_TOP_LEFT_CORNER, 0, 0);
    draw_glyph_on_grid(app, BORDER_TOP_RIGHT_CORNER, gw-1, 0);
    draw_glyph_on_grid(app, BORDER_BOTTOM_LEFT_CORNER, 0, gh-1);
    draw_glyph_on_grid(app, BORDER_BOTTOM_RIGHT_CORNER, gw-1, gh-1);
  } else {
    draw_glyph_on_grid(app, SMALL_BORDER_TOP_LEFT_CORNER, 0, 0);
    draw_glyph_on_grid(app, SMALL_BORDER_TOP_RIGHT_CORNER, gw-1, 0);
    draw_glyph_on_grid(app, SMALL_BORDER_BOTTOM_LEFT_CORNER, 0, gh-1);
    draw_glyph_on_grid(app, SMALL_BORDER_BOTTOM_RIGHT_CORNER, gw-1, gh-1);
  }
  
  // draws the columns
  int r;
  for (r = 1; r<gh-1; r++) {
    set_color(app, WHITE);
    draw_glyph_on_grid(app, SOLID_BLOCK, 0, r);
    draw_glyph_on_grid(app, SOLID_BLOCK, gw-1, r);

    set_color(app, BLUE);
    if (in_focus) {
       draw_glyph_on_grid(app, BORDER_COLUMN_LEFT, 0, r);
       draw_glyph_on_grid(app, BORDER_COLUMN_RIGHT, gw-1, r);
    }
    else {
      draw_glyph_on_grid(app, SMALL_BORDER_COLUMN_LEFT, 0, r);
      draw_glyph_on_grid(app, SMALL_BORDER_COLUMN_RIGHT, gw-1, r);
    }
  }

  // draws the rows
  int c;
  for (c = 1; c<gw-1; c++) {
    set_color(app, WHITE);
    draw_glyph_on_grid(app, SOLID_BLOCK, c, 0);
    draw_glyph_on_grid(app, SOLID_BLOCK, c, gh-1);

    set_color(app, BLUE);
    if (in_focus) {
      draw_glyph_on_grid(app, BORDER_ROW_TOP, c, 0);
      draw_glyph_on_grid(app, BORDER_ROW_BOTTOM, c, gh-1);
    }
    else {
      draw_glyph_on_grid(app, SMALL_BORDER_ROW_TOP, c, 0);
      draw_glyph_on_grid(app, SMALL_BORDER_ROW_BOTTOM, c, gh-1);
    }
  }
}

void draw_titlebar(TempleApp* app) {
  char *title_to_render = malloc(strlen(app->title) + 3 + 1); 
  strcpy(title_to_render, app->title);
  strcat(title_to_render, "...");
  
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  int titlebar_length = gw / 3;

  if (titlebar_length < 3) {
    return;
  }

  if (titlebar_length > strlen(title_to_render)) {
    titlebar_length = strlen(title_to_render);
  }

  int titlebar_start = (gw/2)-(titlebar_length/2);

  set_color(app,BLUE);
  for (int i=titlebar_start-1; i<titlebar_start+titlebar_length; i++) {
     draw_glyph_on_grid(app, SOLID_BLOCK, i, 0);
  }

  char display_buffer[titlebar_length];
  static int current_index = 0;
  static int pixel_offset = 0;

  set_color(app,WHITE);

  for(int i = 0; i < titlebar_length; i++) {
    display_buffer[i] = title_to_render[(i+current_index) % strlen(title_to_render)];
  }

  draw_glyph_sentence(
		      app,
		      display_buffer,
		      titlebar_length,
		      (titlebar_start*app->real_glyph_size)-pixel_offset,
		      0
		      );

  static int frames_since_last_move = 0;
  if (frames_since_last_move >= 70) {
    pixel_offset += 1;
    frames_since_last_move = 0;
  }

  frames_since_last_move += 1;

  if (pixel_offset >= app->real_glyph_size) {
    pixel_offset = 0;
    current_index++;
  }

  if (current_index >= strlen(title_to_render)) {
    current_index = 0;
  }
}

void draw_close_ctrl(TempleApp* app) {
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

void draw_memory_address(TempleApp* app) {
  char str[8];
  sprintf(str, "%x", app);

  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  set_color(app,BLUE);
  for(int i = gw-12; i<gw-4; i++) {
    draw_glyph(app, SOLID_BLOCK, (i*app->real_glyph_size)-2, 0);
  }

  set_color(app,WHITE);
  draw_glyph_sentence(app, str, 8, ((gw-12)*app->real_glyph_size), 0);
}

// draws the window border and decorations
void draw_window_decorations(TempleApp* app) {
  int flags = SDL_GetWindowFlags(app->window);
  draw_window_border(app, flags & SDL_WINDOW_INPUT_FOCUS);
  draw_close_ctrl(app);
  draw_titlebar(app);
  draw_memory_address(app);
}
