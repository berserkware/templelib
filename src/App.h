#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

typedef struct CtrlNode CtrlNode; 

#define WINDOWf_NO_BORDER 1 << 0

// This contains the data and config for the app.
typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  char* title;
  void (*draw_it)();
  int scale;
  int real_glyph_size;
  CtrlNode* ctrl_head;
  int window_flags;
} TempleApp;

// Stops running an app.
void TL_QuitApp(TempleApp* app, int code);

// Creates an App.
TempleApp* TL_CreateApp();

// Runs an App.
void TL_RunApp(TempleApp* app);

#endif
