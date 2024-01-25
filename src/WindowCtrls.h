#ifndef WINDOW_CTRLS_H
#define WINDOW_CTRLS_H

#include <SDL2/SDL.h>
#include "App.h"

// Adds the window ctrls to the app
void AddWindowCtrls(TempleApp* app);

// Updates the ctrls postions to make sure they are in the correct positions
void UpdateWindowCtrls(TempleApp* app);

#endif
