#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "app.h"

// This contains the data about the mouse
struct MouseState {
  struct {        // The position of the mouse in pixels
    int x, y;
  } pos;
  struct {        // The position of the mouse in text columns and rows
    int x, y;
  } pos_text;
  struct {        // The global (screen) position of the mouse in pixels.
    int x, y;
  } global_pos;
  struct {        // The global (screen) position on the mouse in text columns and rows.
    int x, y;
  } global_pos_text;
  
  int lb,         // Left Button
    rb;           // Right Button
};

extern struct MouseState ms;

// updates the ms variable
void update_mouse_state(TempleApp* app);

#endif
