#ifndef TEMPLELIB_H
#define TEMPLELIB_H

// This contains the data and config for the app.
typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  char* title;
  void (*draw_it)();
  int scale;
} TempleApp;

// Creates an App.
TempleApp* tl_create_app();

// Runs an App.
void tl_run_app(TempleApp* app);

#endif
