#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../App.h"
#include "GrGlyphs.h"
#include "GrColors.h"

SDL_Texture* glyphs_texture;
SDL_Rect* glyphs;

void LoadGlyphs(TempleApp* app) {
  SDL_Surface* glyphs_img = IMG_Load(GLYPHSHEET_PATH);

  if (!glyphs_img) {
    printf("Error loading glyphsheet: %s\n", SDL_GetError());
    exit(0);
  }

  // Makes sure glyph sheet is correct size
  if (glyphs_img->w % GLYPH_SIZE != 0) {
    printf("Glyph spritesheet is too wide (must be divisable by the glyph size).\n");
  }

  if (glyphs_img->h % GLYPH_SIZE != 0) {
    printf("Glyph spritesheet is too tall (must be divisable by the glyph size).\n");
  }

  // allocs the glyphs array to store all the glyphs
  int glyph_count = (glyphs_img->w/GLYPH_SIZE)*(glyphs_img->h/GLYPH_SIZE);
  glyphs = malloc(sizeof(SDL_Rect)*glyph_count);
  
  // The index of the glyphs array.
  int i;
  for(i = 0; i<glyph_count; i++) {
    glyphs[i].w = GLYPH_SIZE;
    glyphs[i].h = GLYPH_SIZE;
  }

  // resets the index
  i = 0;
  for(int y = 0; y<glyphs_img->h; y+=GLYPH_SIZE) {
    for(int x = 0; x<glyphs_img->w; x+=GLYPH_SIZE) {
      glyphs[i].x = x;
      glyphs[i].y = y;
      i++;
    }
  }

  glyphs_texture = SDL_CreateTextureFromSurface(app->renderer, glyphs_img);
}

void FreeGlyphs() {
  free(glyphs_texture);
  free(glyphs);
}

int CharToGlyphIndex(char c) {
  if (c < 33) {
    return -1;
  }

  if (c > 126) {
    return -1;
  }

  return c - 33;
}

void DrawGlyph(TempleApp* app, int gi, int x, int y) {
  SDL_Rect dstrect = {x,y, app->real_glyph_size, app->real_glyph_size};
  SDL_RenderCopy(app->renderer, glyphs_texture, &glyphs[gi], &dstrect);
}

void DrawGlyphOnGrid(TempleApp* app, int gi, int gx, int gy) {
  // the actual position on the window
  int x, y;
  x = gx * app->real_glyph_size;
  y = gy * app->real_glyph_size;
  
  DrawGlyph(app, gi, x, y);
}

void DrawGlyphSentence(TempleApp* app, char* sentence, int length, int x, int y) {
  for (int i = 0; i<length; i++) {
    if (sentence[i] == ' ')
      continue;
    DrawGlyph(app, CharToGlyphIndex(sentence[i]), x+(app->real_glyph_size*i), y);
  }
}
