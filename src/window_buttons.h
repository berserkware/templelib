#ifndef WINDOW_BUTTONS_H
#define WINDOW_BUTTONS_H

#include <SDL2/SDL.h>
#include "templelib.h"

// Adds the window buttons to the app
void add_window_buttons(TempleApp* app);

// Updates the button postions to make sure they are in the correct positions
void update_window_buttons(TempleApp* app);

#endif
