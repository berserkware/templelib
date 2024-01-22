#include <SDL2/SDL.h>
#include "templelib.h"
#include "button.h"
#include "window.h"
#include "window_buttons.h"
#include "input.h"

int close_button_id;
int top_move_window_button_id;
int left_move_window_button_id;
int bottom_resize_window_button_id;
int right_resize_window_button_id;

int close_window_button_callback(TempleApp* app);
int move_window_button_callback(TempleApp* app);
int bottom_resize_window_button_callback(TempleApp* app);
int right_resize_window_button_callback(TempleApp* app);


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

  // Adds the bottom resize button.
  Button* bottom_resize_window_button = malloc(sizeof(Button));
  bottom_resize_window_button->length = gw-2;
  bottom_resize_window_button->on_y = 0;
  bottom_resize_window_button->priority = 0;
  bottom_resize_window_button->callback = &bottom_resize_window_button_callback;
  bottom_resize_window_button->pos.x = 1;
  bottom_resize_window_button->pos.y = gh-1;
  bottom_resize_window_button->currently_running = 0;
  bottom_resize_window_button_id = add_button(app, bottom_resize_window_button);

  // Adds the right resize button.
  Button* right_resize_window_button = malloc(sizeof(Button));
  right_resize_window_button->length = gh-1;
  right_resize_window_button->on_y = 1;
  right_resize_window_button->priority = 1;
  right_resize_window_button->callback = &right_resize_window_button_callback;
  right_resize_window_button->pos.x = gw-1;
  right_resize_window_button->pos.y = 0;
  right_resize_window_button->currently_running = 0;
  right_resize_window_button_id = add_button(app, right_resize_window_button);
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
  
  Button* bottom_resize_window_button = get_button(app, bottom_resize_window_button_id);
  bottom_resize_window_button->length = gw-2;
  bottom_resize_window_button->pos.y = gh-1;

  Button* right_resize_window_button = get_button(app, right_resize_window_button_id);
  right_resize_window_button->length = gh-1;
  right_resize_window_button->pos.x = gw-1;
}

int close_window_button_callback(TempleApp* app) {
  tl_quit_app(app, 0);
  return 0;
}

int move_window_button_callback(TempleApp* app) {
  static int has_function_started = 0;
  static struct MouseState starting_mouse_position;

  if (!has_function_started) {
    starting_mouse_position = ms;
    has_function_started = 1;
  }

  if (!ms.lb) {
    has_function_started = 0;
    return 0;
  }

  int is_on_y = starting_mouse_position.pos_text.x == 0;

  if(!is_on_y) {
     SDL_SetWindowPosition(
			   app->window,
			   ((starting_mouse_position.global_pos_text.x-starting_mouse_position.pos_text.x)-(starting_mouse_position.global_pos_text.x-ms.global_pos_text.x))*app->real_glyph_size,
			   ms.global_pos_text.y*app->real_glyph_size
			   );
  } else {
     SDL_SetWindowPosition(
			   app->window,
			   ms.global_pos_text.x*app->real_glyph_size,
			   ((starting_mouse_position.global_pos_text.y-starting_mouse_position.pos_text.y)-(starting_mouse_position.global_pos_text.y-ms.global_pos_text.y))*app->real_glyph_size
			   );
  }

  return 1;
}

int bottom_resize_window_button_callback(TempleApp* app) {
  if (!ms.lb) {
    return 0;
  }

  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  int gx, gy;
  get_window_grid_position(app, &gx, &gy);

  SDL_SetWindowSize(
		    app->window,
		    gw*app->real_glyph_size,
		    (ms.global_pos_text.y - gy+1)*app->real_glyph_size
		    );
  
  return 1;
}

int right_resize_window_button_callback(TempleApp* app) {
  if (!ms.lb) {
    return 0;
  }

  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  int gx, gy;
  get_window_grid_position(app, &gx, &gy);

  SDL_SetWindowSize(
		    app->window,
		    (ms.global_pos_text.x - gx+1)*app->real_glyph_size,
		    gh*app->real_glyph_size
		    );
  
  return 1;
}
