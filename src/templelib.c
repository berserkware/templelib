#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "colors.h"
#include "templelib.h"
#include "glyphs.h"

// Updates the window's postion and size.
static void update_window() {
  
}

// Updates the cursor type
static void update_cursor() {
  
}

// draws the window border and decorations
static void draw_window_decorations() {
}


// runs 30 times per second
static void update_screen(TempleApp* app) {
  SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
  SDL_RenderClear(app->renderer);
  
  update_cursor();
  update_window();
  draw_window_decorations();

  (app->draw_it)();

  SDL_Rect dstrect = {0,0, 32, 32};
  SDL_RenderCopy(app->renderer, glyphs_texture, &glyphs[20], &dstrect);

  SDL_RenderPresent(app->renderer);
}

TempleApp* tl_create_app(int argc, char *argv[]) {
  TempleApp* app = malloc(sizeof(TempleApp));

  // sets default app title
  app->title = "TempleLib App";

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
  
  while (1) {
    update_screen(app);

    sleep(33/1000);
  };
}
