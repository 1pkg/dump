#include "Way.h"

#include <stdlib.h>
#include <time.h>

int seed(int distance, int seed) {
  if (seed == 0)
    srand((int)time(NULL));
  else
    srand(seed);
  return rand() % distance;
}

Way::Way(int width, int len) {
  this->width = width;
  this->len = len;
}

bool Way::gate_Checker(int wall, int position) {
  if ((position != 0) && (position != this->len - 1) &&
      (position != this->width - 1)) {
    switch (wall) {
    case 1:
      if (this->len - position > 0)
        return true;
      else
        return false;
      break;

    case 2:
      if (this->len - position > 0)
        return true;
      else
        return false;
      break;

    case 3:
      if (this->width - position > 0)
        return true;
      else
        return false;
      break;

    case 4:
      if (this->width - position > 0)
        return true;
      else
        return false;
      break;

    default:
      return false;
    }
  } else
    return false;
}

void Way::do_Gate() {
  int wall, position;
  int seeds = 0;

l1:
  seeds = seed(666 * 666 * 666, seeds);
  wall = seeds % 4 + 1;

  position =
      seed(this->len > this->width ? this->len - 1 : this->width - 1, seeds) +
      1;

  if (gate_Checker(wall, position)) {
    switch (wall) {
    case 1:
      this->add_node(0, position);
      this->add_node(1, position);
      break;

    case 2:
      this->add_node(this->width - 1, position);
      this->add_node(this->width - 2, position);
      break;

    case 3:
      this->add_node(position, this->len - 1);
      this->add_node(position, this->len - 2);
      break;

    case 4:
      this->add_node(position, 0);
      this->add_node(position, 1);
      break;
    }
  }

  else
    goto l1;
}

void Way::regen_it() {
  node *enter;

  if (this->head->n < 15) {
    while (this->head->n > 2) {
      enter = this->head->next;
      delete this->head;
      this->head = enter;
    }
  } else {
    for (int i = 0; i < 12; i++) {
      enter = this->head->next;
      delete this->head;
      this->head = enter;
    }
  }
}

bool Way::fin() {

  if (this->head->m_lval == 0 || this->head->m_lval == this->len - 1 ||
      this->head->m_wval == 0 || this->head->m_wval == this->width - 1) {
    node *enter = this->head;

    do
      this->head = this->head->next;
    while (this->head->n != 1);

    if (enter->n < this->len * this->width) {
      this->head = enter;
      this->regen_it();
      return true;
    }

    else if ((this->head->m_lval == enter->m_lval) ||
             (this->head->m_wval == enter->m_wval)) {
      this->head = enter;
      this->regen_it();
      return true;
    }

    else if (((enter->m_lval == 0 || enter->m_lval == this->len - 1) &&
              (this->head->m_wval == 0 ||
               this->head->m_wval == this->width - 1)) ||
             ((this->head->m_lval == 0 ||
               this->head->m_lval == this->len - 1) &&
              (enter->m_wval == 0 || enter->m_wval == this->width - 1))) {
      if (abs(((enter->m_wval * this->len) + enter->m_lval) -
              ((this->head->m_wval * this->len) + this->head->m_lval)) <
          (this->len) * (int)(this->width / 6)) {
        this->head = enter;
        this->regen_it();
        return true;
      }

      else {
        this->head = enter;
        return false;
      }
    }

    else {
      this->head = enter;
      return false;
    }
  }

  else
    return true;
}

bool Way::check_Way(int route, int size) {
  switch (route) {
  case 1:
    if (this->head->m_wval - size >= 0 &&
        (this->head->next->m_wval >= this->head->m_wval))
      return true;
    else
      return false;
    break;

  case 2:
    if (this->head->m_wval + size <= this->width - 1 &&
        (this->head->next->m_wval <= this->head->m_wval))
      return true;
    else
      return false;
    break;

  case 3:
    if (this->head->m_lval + size <= this->len - 1 &&
        (this->head->next->m_lval <= this->head->m_lval))
      return true;
    else
      return false;
    break;

  case 4:
    if (this->head->m_lval - size >= 0 &&
        (this->head->next->m_lval >= this->head->m_lval))
      return true;
    else
      return false;
    break;

  default:
    return false;
  }
}

void Way::do_step(int route, int size) {
  int len, width;

  for (int i = 1; i <= size; i++) {
    width = this->head->m_wval;
    len = this->head->m_lval;

    switch (route) {
    case 1:
      this->add_node(--width, len);
      break;

    case 2:
      this->add_node(++width, len);
      break;

    case 3:
      this->add_node(width, ++len);
      break;

    case 4:
      this->add_node(width, --len);
      break;
    }
  }
}

void Way::do_Way() {
  int seeds = 0;

  while (this->fin()) {
    if (this->head->n % 50 == 0 &&
        (this->head->n > this->width * this->len * 3))
      seeds = 0;

    seeds = seed(666 * 666 * 666, seeds);

    if (this->check_Way(seeds % 4 + 1, seeds % 3 + 2))
      this->do_step(seeds % 4 + 1, seeds % 3 + 2);
  }
}

void Way::position(int &start_width, int &start_len, int &end_width,
                   int &end_len) {
  node *enter = this->head;

  end_width = this->head->m_wval;
  end_len = this->head->m_lval;

  while (this->head->n != 1)
    this->head = this->head->next;

  start_width = this->head->m_wval;
  start_len = this->head->m_lval;

  this->head = enter;
}

void Way::coppy_lab(bool **lab) {
  node *enter = this->head;

  while (this->head != NULL) {
    lab[this->head->m_wval][this->head->m_lval] = 1;
    this->head = this->head->next;
  }

  this->head = enter;
}

void Way::main(bool **lab, int &start_width, int &start_len, int &end_width,
               int &end_len) {
  this->do_Gate();
  this->do_Way();

  this->coppy_lab(lab);
  this->position(start_width, start_len, end_width, end_len);
}

bool Way::check_sWay(int route, int size) {
  switch (route) {
  case 1:
    if (this->head->m_wval - size > 0 &&
        (this->head->next->m_wval >= this->head->m_wval))
      return true;
    else
      return false;
    break;

  case 2:
    if (this->head->m_wval + size < this->width - 1 &&
        (this->head->next->m_wval <= this->head->m_wval))
      return true;
    else
      return false;
    break;

  case 3:
    if (this->head->m_lval + size < this->len - 1 &&
        (this->head->next->m_lval <= this->head->m_lval))
      return true;
    else
      return false;
    break;

  case 4:
    if (this->head->m_lval - size > 0 &&
        (this->head->next->m_lval >= this->head->m_lval))
      return true;
    else
      return false;
    break;

  default:
    return false;
  }
}

void Way::do_sWay() {
  node *enter = head;
  int lim = seed(this->head->n - 1, 0);

  while (this->head->n > lim) {
    enter = this->head->next;
    delete this->head;
    this->head = enter;
  }

  int seeds = 0;

  for (int i = 0; i < this->width * this->len; i++) {
    seeds = seed(666 * 666 * 666, seeds);

    if (this->check_sWay(seeds % 4 + 1, seeds % 6 + 2))
      this->do_step(seeds % 4 + 1, seeds % 6 + 2);
  }
}