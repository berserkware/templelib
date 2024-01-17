#ifndef TEMPLELIB_H
#define TEMPLELIB_H

// This contains the data and config for the app.
typedef struct {
  GtkWidget *window;
  GtkWidget *drawing_area;
  char* title;
  void (*draw_it);
  int border_scale;
  int text_scale;
} TempleApp;


// The app that is currently being run.
extern TempleApp* active_app;

// Creates an App.
TempleApp* tl_create_app();

// Runs an App.
void tl_run_app(TempleApp* app);

#endif
