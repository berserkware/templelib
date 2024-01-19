#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "input.h"
#include "colors.h"
#include "gr.h"
#include "glyphs.h"
#include "templelib.h"
#include "window.h"

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

// runs when the app is started
static void start(TempleApp* app) {
  int window_flags = SDL_WINDOW_BORDERLESS;
  
  app->window = SDL_CreateWindow(
				 app->title,
				 SDL_WINDOWPOS_UNDEFINED,
				 SDL_WINDOWPOS_UNDEFINED,
				 550,
				 800,
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
}

// runs 30 times per second
static void update(TempleApp* app) {
  set_color(app, WHITE);
  SDL_RenderClear(app->renderer);

  update_mouse_state(app);
  update_window(app);
  draw_window_decorations(app);

  (app->draw_it)();

  SDL_RenderPresent(app->renderer);
}

void tl_run_app(TempleApp* app) {
  start(app);

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
    
    update(app);
    
    sleep(0.033);
  };
}

void tl_quit_app(TempleApp* app, int code) {
  free_glyphs();
  SDL_Quit();
  IMG_Quit();
  exit(code);
}
