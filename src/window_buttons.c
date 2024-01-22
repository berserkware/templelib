#include <SDL2/SDL.h>
#include "templelib.h"
#include "button.h"
#include "window.h"
#include "window_buttons.h"
#include "input.h"

int close_button_id;
int top_move_window_button_id;
int left_move_window_button_id;

int close_window_button_callback(TempleApp* app);
int move_window_button_callback(TempleApp* app);

void add_window_buttons(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  // Adds the close window button.
  Button* close_window_button = malloc(sizeof(Button));
  close_window_button->length = 3;
  close_window_button->on_y = 0;
  close_window_button->priority = 2;
  close_window_button->callback = &close_window_button_callback;
  close_window_button->pos.x = gw-4;
  close_window_button->pos.y = 0;
  close_window_button->currently_running = 0;
  close_button_id = add_button(app, close_window_button);

  // Adds the titlebar move button.
  Button* top_move_window_button = malloc(sizeof(Button));
  top_move_window_button->length = gw-2;
  top_move_window_button->on_y = 0;
  top_move_window_button->priority = 1;
  top_move_window_button->callback = &move_window_button_callback;
  top_move_window_button->pos.x = 1;
  top_move_window_button->pos.y = 0;
  top_move_window_button->currently_running = 0;
  top_move_window_button_id = add_button(app, top_move_window_button);

   // Adds the sidebar move button.
  Button* left_move_window_button = malloc(sizeof(Button));
  left_move_window_button->length = gh-1;
  left_move_window_button->on_y = 1;
  left_move_window_button->priority = 1;
  left_move_window_button->callback = &move_window_button_callback;
  left_move_window_button->pos.x = 0;
  left_move_window_button->pos.y = 0;
  left_move_window_button->currently_running = 0;
  left_move_window_button_id = add_button(app, left_move_window_button);
}

void update_window_buttons(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);
  
  Button* close_button = get_button(app, close_button_id);
  close_button->pos.x = gw-4;

  Button* top_move_window_button = get_button(app, top_move_window_button_id);
  top_move_window_button->length = gw-2;

  Button* left_move_window_button = get_button(app, left_move_window_button_id);
  left_move_window_button->length = gh-1;
}

int close_window_button_callback(TempleApp* app) {
  tl_quit_app(app, 0);
  return 0;
}

int move_window_button_callback(TempleApp* app) {
  static int has_mouse_been_updated = 0;
  static struct MouseState last_updated_mouse;

  if (!has_mouse_been_updated) {
    last_updated_mouse = ms;
    has_mouse_been_updated = 1;
  }

  if (!ms.lb) {
    has_mouse_been_updated = 0;
    return 0;
  }

  int gx, gy;
  get_window_grid_position(app, &gx, &gy);
  
  if (last_updated_mouse.global_pos_text.y > ms.global_pos_text.y) {
    SDL_SetWindowPosition(
			  app->window,
			  gx*app->real_glyph_size,
			  (gy-1)*app->real_glyph_size
			  );
  }

  if (last_updated_mouse.global_pos_text.y < ms.global_pos_text.y) {
    SDL_SetWindowPosition(
			  app->window,
			  gx*app->real_glyph_size,
			  (gy+1)*app->real_glyph_size)
      ;
  }
  
  if (last_updated_mouse.global_pos_text.x > ms.global_pos_text.x) {
    SDL_SetWindowPosition(
			  app->window,
			  (gx-1)*app->real_glyph_size,
			  gy*app->real_glyph_size
			  );
  }

  if (last_updated_mouse.global_pos_text.x < ms.global_pos_text.x) {
    SDL_SetWindowPosition(
			  app->window,
			  (gx+1)*app->real_glyph_size,
			  gy*app->real_glyph_size
			  );
  }

  last_updated_mouse = ms;
  return 1;
}
