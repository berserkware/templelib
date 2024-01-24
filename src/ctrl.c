#include <SDL2/SDL.h>
#include "window.h"
#include "input.h"
#include "app.h"
#include "ctrl.h"

// Checks if the mouse is hovering over a ctrl
int is_mouse_over_ctrl(TempleApp* app, const Control* c) {
  if (c->on_y) {
    if (
	ms.pos_text.x == c->pos.x &&
	ms.pos_text.y >= c->pos.y &&
	ms.pos_text.y < c->pos.y+c->length
	) {
      return 1;
    }
    
    return 0;
  }
  
  if (
      ms.pos_text.y == c->pos.y &&
      ms.pos_text.x >= c->pos.x &&
      ms.pos_text.x < c->pos.x+c->length
      ) {
    return 1;
  }

  return 0;
}

void update_ctrls(TempleApp* app) {
  static struct MouseState last_ms;
  CtrlNode* current = app->ctrl_head;

  if(current == NULL) {
    return;
  }

  Control* ctrl_clicked = NULL;
  
  while(current != NULL) {
    if(current->ctrl->currently_running) {
      int still_running = (current->ctrl->callback)(app);
      if (!still_running) {
	current->ctrl->currently_running = 0;
      }
    }
    if(
       is_mouse_over_ctrl(app, current->ctrl) &&
       ms.lb &&
       !last_ms.lb
       ) {
      if (
	  ctrl_clicked != NULL &&
	  ctrl_clicked->priority < current->ctrl->priority
	  ) {
	ctrl_clicked = current->ctrl;
      }

      if (ctrl_clicked == NULL) {
	ctrl_clicked = current->ctrl;
      }
    }
    current=current->next;
  }

  if (ctrl_clicked != NULL) {
    int still_running = (ctrl_clicked->callback)(app);
    if (still_running) {
      ctrl_clicked->currently_running = 1;
    }
  }

  last_ms = ms;
}

int add_ctrl(TempleApp* app, Control* c){
  // stores the id to give to the next CtrlNode
  static int current_id = 1;
  
  CtrlNode* node = malloc(sizeof(CtrlNode));
  node->id = current_id;
  node->ctrl = c;
  node->next = NULL;

  current_id++;
  
  if (app->ctrl_head == NULL) {
    app->ctrl_head = node;
    return node->id;
  }

  CtrlNode* current = app->ctrl_head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = node;
  return node->id;
}

Control* get_ctrl(TempleApp* app, int id) {
  CtrlNode* current = app->ctrl_head;
  while (current != NULL) {
    if (current->id == id) {
      return current->ctrl;
    }
    current = current->next;
  }

  return NULL;
}

int delete_ctrl(TempleApp* app, int id) {
  CtrlNode* current = app->ctrl_head;
  CtrlNode* prev = app->ctrl_head;

  if (current == NULL) {
    return 0;
  }
  
  // Deletes the first element if it matches
  if (current->id == id) {
    app->ctrl_head = current->next;
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
