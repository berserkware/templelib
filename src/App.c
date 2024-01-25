#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "Input.h"
#include "Gr/GrColors.h"
#include "Gr/GrWin.h"
#include "Gr/GrGlyphs.h"
#include "App.h"
#include "Window.h"
#include "WindowCtrls.h"
#include "Ctrl.h"

TempleApp* TL_CreateApp(int argc, char *argv[]) {
  TempleApp* app = malloc(sizeof(TempleApp));

  // sets default app data
  app->title = "Unnamed Task";
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
static void Start(TempleApp* app) {
  int window_flags = SDL_WINDOW_BORDERLESS;
  
  app->window = SDL_CreateWindow(
				 app->title,
				 SDL_WINDOWPOS_UNDEFINED,
				 SDL_WINDOWPOS_UNDEFINED,
				 750,
				 400,
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

  LoadGlyphs(app);

  app->real_glyph_size = app->scale * GLYPH_SIZE;

  AddWindowCtrls(app);
}

// runs 30 times per second
static void Update(TempleApp* app) {
  SetColor(app, WHITE);
  SDL_RenderClear(app->renderer);

  UpdateMouseState(app);
  UpdateWindow(app);
  UpdateCtrls(app);
  UpdateWindowCtrls(app);

  (app->draw_it)();
  DrawWindowDecorations(app);

  SDL_RenderPresent(app->renderer);
}

void TL_RunApp(TempleApp* app) {
  Start(app);

  SDL_Event event;
  
  while (1) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	TL_QuitApp(app, 0);
	break;

      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_ESCAPE:
	  TL_QuitApp(app, 0);
	  break;
	}
	break;

      default:
	break;
      }
    } 
    
    Update(app);
    
    sleep(0.033);
  };
}

void TL_QuitApp(TempleApp* app, int code) {
  FreeGlyphs();
  SDL_Quit();
  IMG_Quit();
  exit(code);
}
