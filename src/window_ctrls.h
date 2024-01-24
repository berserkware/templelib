#ifndef WINDOW_CTRLS_H
#define WINDOW_CTRLS_H

#include <SDL2/SDL.h>
#include "app.h"

// Adds the window ctrls to the app
void add_window_ctrls(TempleApp* app);

// Updates the ctrls postions to make sure they are in the correct positions
void update_window_ctrls(TempleApp* app);

#endif
