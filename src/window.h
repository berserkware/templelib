#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "templelib.h"

void get_window_grid_size(TempleApp* app, int* gw, int* gh);

void update_window(TempleApp* app);

#endif
