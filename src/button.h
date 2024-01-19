#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

typedef TempleApp TempleApp;

// A clickable location on the screen.
typedef struct Button {
  int length,             // The text length of the button
    on_y,                 // If the button goes down instead of across
    priority,             // The button with the highest priority gets clicked on a overlap
    currently_running,    // If the button callback hasn't returned false yet
    (*callback)();        // The callback to execute when the button is pressed
} Button;

// A linked list node for storing buttons with ids, so they can be created and deleted
// easily.
typedef struct ButtonNode {
  int id;
  Button* button;
  struct ButtonNode* next;
} ButtonNode;

// Updates the buttons. Runs and manages the callbacks.
void update_buttons(TempleApp* app);

// Creates a button, returns the id of the button
int create_buttton(TempleApp* app, Button* b);

// Gets a button by it's id. Returns a null pointer if not found
Button* get_button(TempleApp* app, int id);

// Deletes a button. Returns 1 if successful, 0 if the button couldn't be found.
int delete_button(TempleApp* app, int id);

#endif
