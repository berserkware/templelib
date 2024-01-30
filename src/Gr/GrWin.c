#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../Win.h"
#include "../App.h"
#include "GrColors.h"
#include "GrGlyphs.h"
#include "GrWin.h"

// draws the border of the window
void DrawWindowBorder(TempleApp* app, int in_focus) {
  int gw, gh;
  GetWindowGridSize(app, &gw, &gh);

  SetColor(app, WHITE);
  DrawGlyphOnGrid(app, SOLID_BLOCK, 0, 0);
  DrawGlyphOnGrid(app, SOLID_BLOCK, gw-1, 0);
  DrawGlyphOnGrid(app, SOLID_BLOCK, 0, gh-1);
  DrawGlyphOnGrid(app, SOLID_BLOCK, gw-1, gh-1);

  SetColor(app, BLUE);
  // draws the corners
  if (in_focus) {
    DrawGlyphOnGrid(app, BOX_DOUBLE_TOP_LEFT, 0, 0);
    DrawGlyphOnGrid(app, BOX_DOUBLE_TOP_RIGHT, gw-1, 0);
    DrawGlyphOnGrid(app, BOX_DOUBLE_BOTTOM_LEFT, 0, gh-1);
    DrawGlyphOnGrid(app, BOX_DOUBLE_BOTTOM_RIGHT, gw-1, gh-1);
  } else {
    DrawGlyphOnGrid(app, BOX_SINGLE_TOP_LEFT, 0, 0);
    DrawGlyphOnGrid(app, BOX_SINGLE_TOP_RIGHT, gw-1, 0);
    DrawGlyphOnGrid(app, BOX_SINGLE_BOTTOM_LEFT, 0, gh-1);
    DrawGlyphOnGrid(app, BOX_SINGLE_BOTTOM_RIGHT, gw-1, gh-1);
  }
  
  // draws the columns
  int r;
  for (r = 1; r<gh-1; r++) {
    SetColor(app, WHITE);
    DrawGlyphOnGrid(app, SOLID_BLOCK, 0, r);
    DrawGlyphOnGrid(app, SOLID_BLOCK, gw-1, r);

    SetColor(app, BLUE);
    if (in_focus) {
      DrawGlyphOnGrid(app, BOX_DOUBLE_HORIZONTAL, 0, r);
      DrawGlyphOnGrid(app, BOX_DOUBLE_HORIZONTAL, gw-1, r);
    }
    else {
      DrawGlyphOnGrid(app, BOX_SINGLE_HORIZONTAL, 0, r);
      DrawGlyphOnGrid(app, BOX_SINGLE_HORIZONTAL, gw-1, r);
    }
  }

  // draws the rows
  int c;
  for (c = 1; c<gw-1; c++) {
    SetColor(app, WHITE);
    DrawGlyphOnGrid(app, SOLID_BLOCK, c, 0);
    DrawGlyphOnGrid(app, SOLID_BLOCK, c, gh-1);

    SetColor(app, BLUE);
    if (in_focus) {
      DrawGlyphOnGrid(app, BOX_DOUBLE_VERTICAL, c, 0);
      DrawGlyphOnGrid(app, BOX_DOUBLE_VERTICAL, c, gh-1);
    }
    else {
      DrawGlyphOnGrid(app, BOX_SINGLE_VERTICAL, c, 0);
      DrawGlyphOnGrid(app, BOX_SINGLE_VERTICAL, c, gh-1);
    }
  }
}

void DrawTitlebar(TempleApp* app) {
  char *title_to_render = malloc(strlen(app->title) + 3 + 1); 
  strcpy(title_to_render, app->title);
  strcat(title_to_render, "...");
  
  int gw, gh;
  GetWindowGridSize(app, &gw, &gh);

  int titlebar_length = gw / 3;

  if (titlebar_length < 3) {
    return;
  }

  if (titlebar_length > strlen(title_to_render)) {
    titlebar_length = strlen(title_to_render);
  }

  int titlebar_start = (gw/2)-(titlebar_length/2);

  SetColor(app,BLUE);
  for (int i=titlebar_start-1; i<titlebar_start+titlebar_length; i++) {
     DrawGlyphOnGrid(app, SOLID_BLOCK, i, 0);
  }

  char display_buffer[titlebar_length];
  static int current_index = 0;
  static int pixel_offset = 0;

  SetColor(app,WHITE);

  for(int i = 0; i < titlebar_length; i++) {
    display_buffer[i] = title_to_render[(i+current_index) % strlen(title_to_render)];
  }

  DrawGlyphSentence(
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

void DrawCloseCtrl(TempleApp* app) {
  int gw, gh;
  GetWindowGridSize(app, &gw, &gh);
  
  SetColor(app, WHITE);
  DrawGlyphOnGrid(app, SOLID_BLOCK, gw-2, 0);
  DrawGlyphOnGrid(app, SOLID_BLOCK, gw-3, 0);
  DrawGlyphOnGrid(app, SOLID_BLOCK, gw-4, 0);

  SetColor(app,BLUE);
  DrawGlyphOnGrid(app, CharToGlyphIndex(']'), gw-2, 0);
  DrawGlyphOnGrid(app, CharToGlyphIndex('X'), gw-3, 0);
  DrawGlyphOnGrid(app, CharToGlyphIndex('['), gw-4, 0);
}

void DrawMemoryAddress(TempleApp* app) {
  char str[8];
  sprintf(str, "%x", app);

  int gw, gh;
  GetWindowGridSize(app, &gw, &gh);

  SetColor(app,BLUE);
  for(int i = gw-12; i<gw-4; i++) {
    DrawGlyph(app, SOLID_BLOCK, (i*app->real_glyph_size), 0);
  }

  SetColor(app,WHITE);
  DrawGlyphSentence(app, str, 8, ((gw-12)*app->real_glyph_size), 0);
}

// draws the window border and decorations
void DrawWindowDecorations(TempleApp* app) {
  int flags = SDL_GetWindowFlags(app->window);
  if (!(app->window_flags & WINDOWf_NO_BORDER)) {
    DrawWindowBorder(app, flags & SDL_WINDOW_INPUT_FOCUS);
    DrawCloseCtrl(app);
    DrawTitlebar(app);
    DrawMemoryAddress(app);
  }
}
