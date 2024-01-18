#ifndef GLYPHS_H
#define GLYPHS_H

// Defines the index of the border glyphs
#define BORDER_COLUMN_LEFT 94
#define BORDER_COLUMN_RIGHT 95
#define BORDER_TOP_LEFT_CORNER 96
#define BORDER_TOP_RIGHT_CORNER 97
#define BORDER_BOTTOM_LEFT_CORNER 98
#define BORDER_BOTTOM_RIGHTCORNER 99
#define BORDER_ROW_TOP 100
#define BORDER_ROW_BOTTOM 101

extern SDL_Texture* glyphs_texture;

extern SDL_Rect* glyphs;

void load_glyphs();

#endif