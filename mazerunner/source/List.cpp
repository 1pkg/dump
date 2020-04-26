#include "List.h"

#include <stdlib.h>

List::List() { this->head = NULL; }

void List::add_node(int width, int len) {
  node *new_node = new node;

  new_node->m_lval = len;
  new_node->m_wval = width;

  if (this->head == NULL)
    new_node->n = 1;
  else
    new_node->n = this->head->n + 1;

  new_node->next = this->head;
  this->head = new_node;
}

List::~List() {
  node *current;

  while (this->head != NULL) {
    current = this->head->next;
    delete this->head;
    this->head = current;
  }
}
