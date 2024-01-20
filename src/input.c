#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "input.h"
#include "window.h"
#include "templelib.h"

struct MouseState ms;

void update_mouse_state(TempleApp* app) {  
  // Update the pos, and gets the buttons.
  int buttons = SDL_GetMouseState(&ms.pos.x, &ms.pos.y);

  if (ms.pos.x < 0) {
    ms.pos.x = 0;
  }
  
  if (ms.pos.y < 0) {
    ms.pos.y = 0;
  }

  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);
  if (ms.pos.x > w-1) {
    ms.pos.x = w-1;
  }
  if (ms.pos.y > h-1) {
    ms.pos.y = h-1;
  }
  
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
  
  ms.pos_text.x = (ms.pos.x / app->real_glyph_size);
  ms.pos_text.y = (ms.pos.y / app->real_glyph_size);

  // Updates the global postion
  SDL_GetGlobalMouseState(&ms.global_pos.x, &ms.global_pos.y);

  ms.global_pos_text.x = (ms.global_pos.x / app->real_glyph_size);
  ms.global_pos_text.y = (ms.global_pos.y / app->real_glyph_size);
}
