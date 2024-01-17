#ifndef TEMPLELIB_H
#define TEMPLELIB_H

typedef struct {
  GtkWidget *window;
  GtkWidget *drawing_area;
  char* title;
  void (*draw_it);
} TempleApp;

extern TempleApp* active_app;

TempleApp* tl_create_app();

void tl_run_app(TempleApp* app);

#endif
