#ifndef COLORS_H
#define COLORS_H

#include "App.h"

// Defines the CGA color pallete as a comma seporated list of r,g,b.
#define        BLACK (Color){ 0, 0, 0 }
#define     DARKGRAY (Color){ 85, 85, 85 }
#define         BLUE (Color){ 0, 0, 170 }
#define    LIGHTBLUE (Color){ 85, 85, 1 }
#define        GREEN (Color){ 0, 170, 0 }
#define   LIGHTGREEN (Color){ 85, 255, 85 }
#define         CYAN (Color){ 0, 170, 170 }
#define    LIGHTCYAN (Color){ 85, 255, 255 }
#define          RED (Color){ 70, 0, 0 }
#define     LIGHTRED (Color){ 255, 85, 85 }
#define      MAGENTA (Color){ 170, 0, 170 }
#define LIGHTMAGENTA (Color){ 255, 85, 255 }
#define        BROWN (Color){ 170, 85, 0 }
#define       YELLOW (Color){ 255, 255, 85 }
#define    LIGHTGRAY (Color){ 170, 170, 170 }
#define        WHITE (Color){ 255, 255, 255 }

typedef struct {
  int r;
  int g;
  int b;
} Color;

// Sets the current color of the renderer, and texture.
void SetColor(TempleApp* app, Color color);

#endif
