#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

typedef TempleApp TempleApp;

// A clickable location on the screen.
typedef struct Ctrl {
  struct {                // The position of the button in text.
    int x, y;
  } pos;
  int length,             // The text length of the button
    on_y,                 // If the button goes down instead of across
    priority,             // The button with the highest priority gets clicked on a overlap
    currently_running,    // If the button callback hasn't returned false yet
    (*callback)(TempleApp* app);        // The callback to execute when the button is pressed
} Ctrl;

// A linked list node for storing ctrls with ids, so they can be created and deleted
// easily.
typedef struct CtrlNode {
  int id;
  Ctrl* ctrl;
  struct CtrlNode* next;
} CtrlNode;

// Updates the ctrls. Runs and manages the callbacks.
void UpdateCtrls(TempleApp* app);

// Adds a ctrl to an app, returns the id of the ctrl
int AddCtrl(TempleApp* app, Ctrl* c);

// Gets a ctrl by it's id. Returns a null pointer if not found
Ctrl* GetCtrl(TempleApp* app, int id);

// Deletes a ctrl. Returns 1 if successful, 0 if the ctrl couldn't be found.
int DeleteCtrl(TempleApp* app, int id);

#endif
