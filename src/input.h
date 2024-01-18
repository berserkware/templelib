#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "templelib.h"

// This contains the data about the mouse
struct MouseState {
  int x,          // x postion in pixels
    y,            // y postion in pixels
    x_text,       // x postion in text columns
    y_text,       // y postion in text rows
    
    real_x,       // These four are the last four, but include the window border
    real_y,       // You should not use these directory, Use the ones wihtout
    real_x_text,  // the real_ prefix.
    real_y_text,  //
    
    lb,           // Left Button
    rb;            // Right Button
};

extern struct MouseState ms;

// updates the ms variable
void update_mouse_state(TempleApp* app);

#endif
