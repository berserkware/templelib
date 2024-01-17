#include <gtk/gtk.h>
#include <unistd.h>
#include "colors.h"
#include "templelib.h"

TempleApp* active_app = NULL;

static void draw_window_decorations(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  GtkAllocation allocation;
  gtk_widget_get_allocation(active_app->window, &allocation);

  int window_width = allocation.width;
  int window_height = allocation.height;
  
  cairo_set_source_rgb(cr, WHITE); 
  cairo_paint(cr);
  cairo_set_source_rgb(cr, LIGHTBLUE); 
  cairo_rectangle(cr, 10, 10, window_width - 20, window_height - 20);
  cairo_stroke(cr);
  cairo_rectangle(cr, 5, 5, window_width - 10, window_height - 10);
  cairo_stroke(cr);
}

static void draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  draw_window_decorations(widget, cr, user_data);

}

static gboolean update_drawing_area(gpointer data) {
    gtk_widget_queue_draw(active_app->drawing_area);  // Queue a redraw
    return TRUE;  // Continue the timer
}

TempleApp* tl_create_app(int argc, char *argv[]) {
  TempleApp* app = malloc(sizeof(TempleApp));

  gtk_init(&argc, &argv);

  app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // removes the window decorations for the window, so we can handle it ourselves.
  gtk_window_set_decorated(GTK_WINDOW(app->window), FALSE);
  gtk_window_set_default_size(GTK_WINDOW(app->window), 320, 220);
  
  app->drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(app->window), app->drawing_area);

  g_signal_connect(G_OBJECT(app->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(app->drawing_area), "draw", G_CALLBACK(draw_event), NULL);

  // adds a 30 fps timer to emulate TempleOS's 30 fps cap.
  g_timeout_add(33, (GSourceFunc)update_drawing_area, NULL);
  
  return app;
}

void tl_run_app(TempleApp* app) {
  active_app = app;
  
  gtk_widget_show_all(app->window);
  gtk_main();
}
