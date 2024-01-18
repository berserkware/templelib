#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "input.h"
#include "templelib.h"

struct MouseState ms;

// TODO: There seem to be a bug where if you hold down the left mouse button,
// The real_y and real_x don't stop are the border.
void update_mouse_state(TempleApp* app) {  
  // Update the real_x and real_y, and gets the buttons.
  int buttons = SDL_GetMouseState(&ms.real_x, &ms.real_y);

  // updates the left button
  if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
    ms.lb = 1;
  } else {
    ms.lb = 0;
  }

  // updates the right button
  if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
    ms.rb = 1;
  } else {
    ms.rb = 0;
  }

  int gw, gh;
  get_window_grid_size(app, &gw, &gh);
  
  ms.real_x_text = (ms.real_x / app->real_glyph_size);
  ms.real_y_text = (ms.real_y / app->real_glyph_size);

  // updates the x_text and y_text
  if (ms.real_x_text >= 1) {
    ms.x_text = ms.real_x_text - 1;
  }
  if (ms.real_x_text >= gw-1) {
    ms.x_text = gw-3;
  }
  if (ms.real_y_text >= 1) {
    ms.y_text = ms.real_y_text - 1;
  }
  if (ms.real_y_text >= gh-1) {
    ms.y_text = gh-3;
  }

  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);
  
  //updates the x and y
  if(ms.real_x > app->real_glyph_size) {
    ms.x = ms.real_x - app->real_glyph_size;
    ms.x--;
  }
  if (ms.real_x >= w-app->real_glyph_size) {
    ms.x = w-(app->real_glyph_size*2);
    ms.x--;
  }
  if (ms.real_y > app->real_glyph_size) {
    ms.y = ms.real_y - app->real_glyph_size;
    ms.y--;
  }
  if (ms.real_y >= h-app->real_glyph_size) {
    ms.y = h-(app->real_glyph_size*2);
    ms.y--;
  }
}
