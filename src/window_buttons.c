#include <SDL2/SDL.h>
#include "templelib.h"
#include "button.h"
#include "window.h"
#include "window_buttons.h"

int close_button_id;

int close_window_button_callback(TempleApp* app);

void add_window_buttons(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);
  
  Button* close_window_button = malloc(sizeof(Button));
  close_window_button->length = 3;
  close_window_button->on_y = 0;
  close_window_button->priority = 2;
  close_window_button->callback = &close_window_button_callback;
  close_window_button->pos.x = gw-4;
  close_window_button->pos.y = 0;
  close_window_button->currently_running = 0;
  close_button_id = add_button(app, close_window_button);
}

void update_window_buttons(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);
  
  Button* close_button = get_button(app, close_button_id);
  close_button->pos.x = gw-4;
}

int close_window_button_callback(TempleApp* app) {
  tl_quit_app(app, 0);
  return 0;
}
