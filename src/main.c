#include <stdio.h>
//#include <SDL2/SDL.h>
#include "templelib.h"
#include "gr.h"
#include "doc.h"

void draw_it() {
}

int main(int argc, char *argv[]) {
  TempleApp* app = tl_create_app(argc, argv);

  app->draw_it = &draw_it;
  
  tl_run_app(app);
  
  return 0;
}
