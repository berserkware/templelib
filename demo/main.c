#include <stdio.h>
#include "Templelib.h"

TempleApp* app;

void draw_it() {
  SetColor(app, BLUE);
  DrawGlyphOnGrid(app, 0, ms.pos_text.x, ms.pos_text.y);
}

int main(int argc, char *argv[]) {
  app = TL_CreateApp(argc, argv);

  app->draw_it = &draw_it;
  
  TL_RunApp(app);
  
  return 0;
}
