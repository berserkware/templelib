#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "colors.h"
#include "gr.h"
#include "glyphs.h"
#include "templelib.h"

// Gets the window grid size by dividing the window width by the
// scaled glyph size
void get_window_grid_size(TempleApp* app, int* gw, int* gh) {
  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);

  *gw = w / app->real_glyph_size;
  *gh = h / app->real_glyph_size;
}

// Updates the window's postion and size.
void update_window(TempleApp* app) {

  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);
  
  // Makes sure window width and height is alligned with spritet size
  if (w % app->real_glyph_size != 0) {
    SDL_SetWindowSize(app->window, w-(w % app->real_glyph_size), h);
  }
  if (h % app->real_glyph_size != 0) {
    SDL_SetWindowSize(app->window, w, h-(h % app->real_glyph_size));
  }
}

// Updates the cursor type
void update_cursor(TempleApp* app) {
  
}

// draws the border of the window
void draw_window_border(TempleApp* app) {
  int gw, gh;
  get_window_grid_size(app, &gw, &gh);

  set_color(app, BLUE);

  // draws the corners
  draw_glyph_on_grid(app, BORDER_TOP_LEFT_CORNER, 0, 0);
  draw_glyph_on_grid(app, BORDER_TOP_RIGHT_CORNER, gw-1, 0);
  draw_glyph_on_grid(app, BORDER_BOTTOM_LEFT_CORNER, 0, gh-1);
  draw_glyph_on_grid(app, BORDER_BOTTOM_RIGHT_CORNER, gw-1, gh-1);

  // draws the columns
  int r;
  for (r = 1; r<gh-1; r++) {
     draw_glyph_on_grid(app, BORDER_COLUMN_LEFT, 0, r);
  }
  for (r = 1; r<gh-1; r++) {
     draw_glyph_on_grid(app, BORDER_COLUMN_RIGHT, gw-1, r);
  }

  // draws the rows
  int c;
  for (c = 1; c<gw-1; c++) {
     draw_glyph_on_grid(app, BORDER_ROW_TOP, c, 0);
  }
  for (c = 1; c<gw-1; c++) {
     draw_glyph_on_grid(app, BORDER_ROW_BOTTOM, c, gh-1);
  }
}

// draws the window border and decorations
void draw_window_decorations(TempleApp* app) {
  draw_window_border(app);
}

// runs 30 times per second
static void update_screen(TempleApp* app) {
  set_color(app, WHITE);
  SDL_RenderClear(app->renderer);

  update_window(app);
  update_cursor(app);
  draw_window_decorations(app);

  (app->draw_it)();
    
  SDL_RenderPresent(app->renderer);
}

TempleApp* tl_create_app(int argc, char *argv[]) {
  TempleApp* app = malloc(sizeof(TempleApp));

  // sets default app data
  app->title = "TempleLib App";
  app->scale = 2;
  
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  if (IMG_Init(IMG_INIT_PNG) < 0) {
    printf("Could not init SDL_image: %s\n", IMG_GetError());
    exit(1);
  }
  
  return app;
}

void tl_run_app(TempleApp* app) {
  int window_flags = SDL_WINDOW_BORDERLESS;
  
  app->window = SDL_CreateWindow(
				 app->title,
				 SDL_WINDOWPOS_UNDEFINED,
				 SDL_WINDOWPOS_UNDEFINED,
				 300,
				 200,
				 window_flags
				 );

  if (!app->window) {
    printf("Failed to open window: %s\n", SDL_GetError());
    exit(1);
  }

  int renderer_flags = SDL_RENDERER_ACCELERATED;

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  app->renderer = SDL_CreateRenderer(app->window, -1, renderer_flags);

  if (!app->renderer) {
    printf("Failed to create renderer: %s\n", SDL_GetError());
  }

  load_glyphs(app);

  app->real_glyph_size = app->scale * GLYPH_SIZE;

  SDL_Event event;
  
  while (1) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	tl_quit_app(app, 0);
	break;

      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_ESCAPE:
	  tl_quit_app(app, 0);
	  break;
	}
	break;

      default:
	break;
      }
    } 
    
    update_screen(app);
    
    sleep(0.033);
  };
}

void tl_quit_app(TempleApp* app, int code) {
  free_glyphs();
  SDL_Quit();
  IMG_Quit();
  exit(code);
}
