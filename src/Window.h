#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "App.h"

void GetWindowGridSize(TempleApp* app, int* gw, int* gh);

void GetWindowGridPosition(TempleApp* app, int* gx, int* gy);

void UpdateWindow(TempleApp* app);

#endif
