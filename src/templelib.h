#ifndef TEMPLELIB_H
#define TEMPLELIB_H

#include <SDL2/SDL.h>

// This contains the data and config for the app.
typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  char* title;
  void (*draw_it)();
  int scale;
  int real_glyph_size;
} TempleApp;

// Gets the window grid size by dividing the window width by the
// scaled glyph size
void get_window_grid_size(TempleApp* app, int* gw, int* gh);

// Stops running an app.
void tl_quit_app(TempleApp* app, int code);

// Creates an App.
TempleApp* tl_create_app();

// Runs an App.
void tl_run_app(TempleApp* app);

#endif
