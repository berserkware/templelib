#include <stdio.h>
#include "templelib.h"
#include "gr.h"
#include "input.h"
#include "colors.h"

TempleApp* app;

void draw_it() {
  set_color(app, BLUE);
  draw_glyph_on_grid(app, 0, ms.pos_text.x, ms.pos_text.y);
}

int main(int argc, char *argv[]) {
  app = tl_create_app(argc, argv);

  app->draw_it = &draw_it;
  
  tl_run_app(app);
  
  return 0;
}
