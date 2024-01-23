#include <SDL2/SDL.h>
#include "templelib.h"
#include "ctrl.h"
#include "window.h"
#include "window_ctrls.h"
#include "input.h"

int close_ctrl_id;
int top_move_window_ctrl_id;
int left_move_window_ctrl_id;
int bottom_resize_window_ctrl_id;
int right_resize_window_ctrl_id;
int bottom_right_resize_window_ctrl_id;

int close_window_ctrl_callback(TempleApp* app);
int move_window_ctrl_callback(TempleApp* app);
int bottom_resize_window_ctrl_callback(TempleApp* app);
int right_resize_window_ctrl_callback(TempleApp* app);
int bottom_right_resize_window_ctrl_callback(TempleApp* app);


void add_window_ctrls(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  // Adds the close window ctrl.
  Control* close_window_ctrl = malloc(sizeof(Control));
  close_window_ctrl->length = 3;
  close_window_ctrl->on_y = 0;
  close_window_ctrl->priority = 2;
  close_window_ctrl->callback = &close_window_ctrl_callback;
  close_window_ctrl->pos.x = gw-4;
  close_window_ctrl->pos.y = 0;
  close_window_ctrl->currently_running = 0;
  close_ctrl_id = add_ctrl(app, close_window_ctrl);

  // Adds the titlebar move ctrl.
  Control* top_move_window_ctrl = malloc(sizeof(Control));
  top_move_window_ctrl->length = gw-2;
  top_move_window_ctrl->on_y = 0;
  top_move_window_ctrl->priority = 1;
  top_move_window_ctrl->callback = &move_window_ctrl_callback;
  top_move_window_ctrl->pos.x = 1;
  top_move_window_ctrl->pos.y = 0;
  top_move_window_ctrl->currently_running = 0;
  top_move_window_ctrl_id = add_ctrl(app, top_move_window_ctrl);

  // Adds the sidebar move ctrl.
  Control* left_move_window_ctrl = malloc(sizeof(Control));
  left_move_window_ctrl->length = gh-1;
  left_move_window_ctrl->on_y = 1;
  left_move_window_ctrl->priority = 1;
  left_move_window_ctrl->callback = &move_window_ctrl_callback;
  left_move_window_ctrl->pos.x = 0;
  left_move_window_ctrl->pos.y = 0;
  left_move_window_ctrl->currently_running = 0;
  left_move_window_ctrl_id = add_ctrl(app, left_move_window_ctrl);

  // Adds the bottom resize ctrl.
  Control* bottom_resize_window_ctrl = malloc(sizeof(Control));
  bottom_resize_window_ctrl->length = gw-2;
  bottom_resize_window_ctrl->on_y = 0;
  bottom_resize_window_ctrl->priority = 0;
  bottom_resize_window_ctrl->callback = &bottom_resize_window_ctrl_callback;
  bottom_resize_window_ctrl->pos.x = 1;
  bottom_resize_window_ctrl->pos.y = gh-1;
  bottom_resize_window_ctrl->currently_running = 0;
  bottom_resize_window_ctrl_id = add_ctrl(app, bottom_resize_window_ctrl);

  // Adds the right resize ctrl.
  Control* right_resize_window_ctrl = malloc(sizeof(Control));
  right_resize_window_ctrl->length = gh-1;
  right_resize_window_ctrl->on_y = 1;
  right_resize_window_ctrl->priority = 1;
  right_resize_window_ctrl->callback = &right_resize_window_ctrl_callback;
  right_resize_window_ctrl->pos.x = gw-1;
  right_resize_window_ctrl->pos.y = 0;
  right_resize_window_ctrl->currently_running = 0;
  right_resize_window_ctrl_id = add_ctrl(app, right_resize_window_ctrl);

   // Adds the right resize ctrl.
  Control* bottom_right_resize_window_ctrl = malloc(sizeof(Control));
  bottom_right_resize_window_ctrl->length = 1;
  bottom_right_resize_window_ctrl->on_y = 1;
  bottom_right_resize_window_ctrl->priority = 1;
  bottom_right_resize_window_ctrl->callback = &bottom_right_resize_window_ctrl_callback;
  bottom_right_resize_window_ctrl->pos.x = gw-1;
  bottom_right_resize_window_ctrl->pos.y = gh-1;
  bottom_right_resize_window_ctrl->currently_running = 0;
  bottom_right_resize_window_ctrl_id = add_ctrl(app, bottom_right_resize_window_ctrl);
}

void update_window_ctrls(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);
  
  Control* close_ctrl = get_ctrl(app, close_ctrl_id);
  close_ctrl->pos.x = gw-4;

  Control* top_move_window_ctrl = get_ctrl(app, top_move_window_ctrl_id);
  top_move_window_ctrl->length = gw-2;

  Control* left_move_window_ctrl = get_ctrl(app, left_move_window_ctrl_id);
  left_move_window_ctrl->length = gh-1;
  
  Control* bottom_resize_window_ctrl = get_ctrl(app, bottom_resize_window_ctrl_id);
  bottom_resize_window_ctrl->length = gw-2;
  bottom_resize_window_ctrl->pos.y = gh-1;

  Control* right_resize_window_ctrl = get_ctrl(app, right_resize_window_ctrl_id);
  right_resize_window_ctrl->length = gh-1;
  right_resize_window_ctrl->pos.x = gw-1;

  Control* bottom_right_resize_window_ctrl = get_ctrl(app, bottom_right_resize_window_ctrl_id);
  bottom_right_resize_window_ctrl->length = gh-1;
  bottom_right_resize_window_ctrl->pos.x = gw-1;
}

int close_window_ctrl_callback(TempleApp* app) {
  tl_quit_app(app, 0);
  return 0;
}

int move_window_ctrl_callback(TempleApp* app) {
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

int bottom_resize_window_ctrl_callback(TempleApp* app) {
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

int right_resize_window_ctrl_callback(TempleApp* app) {
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

int bottom_right_resize_window_ctrl_callback(TempleApp* app) {
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
		    (ms.global_pos_text.y - gy+1)*app->real_glyph_size
		    );
  
  return 1;
}
