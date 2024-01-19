#include <SDL2/SDL.h>
#include "templelib.h"
#include "button.h"

void update_buttons(TempleApp* app) {

}

int create_buttton(TempleApp* app, Button* b){
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
  while (current->next != NULL) {
    if (current->id == id) {
      return current->button;
    }
    current = current->next;
  }

  if (current->id == id) {
    return current->button;
  }

  return NULL;
}

// TODO: Bug where if id is first item, it might cause an error.
int delete_button(TempleApp* app, int id) {
  ButtonNode* current = app->button_head;
  ButtonNode* prev = app->button_head;
  
  while (current->next != NULL) {
    if (current->id == id) {
      prev->next = current->next;
      free(current);
      return 1;
    }
    prev=current;
    current = current->next;
  }

  if (current->id == id) {
     prev = current->next;
     free(current);
     return 1;
   }

  return 0;
}
