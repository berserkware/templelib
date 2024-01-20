#include <SDL2/SDL.h>
#include "window.h"
#include "input.h"
#include "templelib.h"
#include "button.h"

// Checks if the mouse is hovering over a button
int is_mouse_over_button(TempleApp* app, const Button* b) {
  if (b->on_y) {
    if (
	ms.pos_text.x == b->pos.x &&
	ms.pos_text.y >= b->pos.y &&
	ms.pos_text.y < b->pos.y+b->length
	) {
      return 1;
    }
    
    return 0;
  }
  
  if (
      ms.pos_text.y == b->pos.y &&
      ms.pos_text.x >= b->pos.x &&
      ms.pos_text.x < b->pos.x+b->length
      ) {
    return 1;
  }

  return 0;
}

void update_buttons(TempleApp* app) {
  static struct MouseState last_ms;
  ButtonNode* current = app->button_head;

  if(current == NULL) {
    return;
  }

  Button* button_clicked = NULL;
  
  while(current != NULL) {
    if(current->button->currently_running) {
      int still_running = (current->button->callback)(app);
      if (!still_running) {
	current->button->currently_running = 0;
      }
    }
    if(
       is_mouse_over_button(app, current->button) &&
       ms.lb &&
       !last_ms.lb
       ) {
      if (
	  button_clicked != NULL &&
	  button_clicked->priority < current->button->priority
	  ) {
	button_clicked = current->button;
      }

      if (button_clicked == NULL) {
	button_clicked = current->button;
      }
    }
    current=current->next;
  }

  if (button_clicked != NULL) {
    int still_running = (button_clicked->callback)(app);
    if (still_running) {
      button_clicked->currently_running = 1;
    }
  }

  last_ms = ms;
}

int add_button(TempleApp* app, Button* b){
  // stores the id to give to the next ButtonNode
  static int current_id = 1;
  
  ButtonNode* node = malloc(sizeof(ButtonNode));
  node->id = current_id;
  node->button = b;
  node->next = NULL;

  current_id++;
  
  if (app->button_head == NULL) {
    app->button_head = node;
    return node->id;
  }

  ButtonNode* current = app->button_head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = node;
  return node->id;
}

Button* get_button(TempleApp* app, int id) {
  ButtonNode* current = app->button_head;
  while (current != NULL) {
    if (current->id == id) {
      return current->button;
    }
    current = current->next;
  }

  return NULL;
}

int delete_button(TempleApp* app, int id) {
  ButtonNode* current = app->button_head;
  ButtonNode* prev = app->button_head;

  if (current == NULL) {
    return 0;
  }
  
  // Deletes the first element if it matches
  if (current->id == id) {
    app->button_head = current->next;
    free(current);
    return 1;
  }
  
  while (current != NULL) {
    if (current->id == id) {
      prev->next = current->next;
      free(current);
      return 1;
    }
    prev=current;
    current = current->next;
  }

  return 0;
}
