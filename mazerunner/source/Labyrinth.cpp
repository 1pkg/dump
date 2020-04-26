#include "Labyrinth.h"
#include "Bot.h"
#include "Visual.h"

#include <Windows.h>
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Labyrinth::input_size(int width, int len) {
  this->width = width;
  this->len = len;

  this->lab = new bool *[this->width];
  for (int i = 0; i < this->width; i++)
    this->lab[i] = new bool[this->len];
}

void Labyrinth::regen_Labirint() {

  for (int i = 0; i < this->width; i++)
    for (int j = 0; j < this->len; j++)
      lab[i][j] = 0;

  this->way = new Way(this->width, this->len);
  this->way->main(lab, this->start.m_width, this->start.m_len,
                  this->end.m_width, this->end.m_len);

  do
    this->clean_up_Labirint();
  while (this->analyse_Labirint());

  delete this->way;
}

void Labyrinth::clean_up_Labirint() {
  for (int i = 0; i < this->width; i++)
    for (int j = 0; j < this->len; j++)
      if (i > 0 && i < this->width - 1)
        if (this->lab[i][j] == 1 && this->lab[i + 1][j] == 1 &&
            this->lab[i - 1][j] == 1) {
          this->p[0].m_width = i;
          this->p[0].m_len = j;

          while (this->lab[i][j] == 1 && this->lab[i + 1][j] == 1 &&
                 this->lab[i - 1][j] == 1) {
            j++;
            if (j >= this->width - 1)
              break;
          }

          this->p[1].m_width = i;
          this->p[1].m_len = j;

          if ((this->p[1].m_len - this->p[0].m_len) >= 3)
            for (int y = this->p[0].m_len + 1; y < this->p[1].m_len - 1; y++)
              this->lab[this->p[0].m_width][y] = 0;

          for (int z = 0; z < 2; z++) {
            this->p[z].m_width = 0;
            this->p[z].m_len = 0;
          }
        }

  for (int j = 0; j < this->len; j++)
    for (int i = 0; i < this->width; i++)
      if (i > 0 && i < this->len - 1)
        if (this->lab[i][j] == 1 && this->lab[i][j + 1] == 1 &&
            this->lab[i][j - 1] == 1) {
          this->p[0].m_width = i;
          this->p[0].m_len = j;

          while (this->lab[i][j] == 1 && this->lab[i][j + 1] == 1 &&
                 this->lab[i][j - 1] == 1) {
            i++;
            if (i >= this->len - 1)
              break;
          }

          this->p[1].m_width = i;
          this->p[1].m_len = j;

          if ((this->p[1].m_width - this->p[0].m_width) >= 3)
            for (int y = this->p[0].m_width + 1; y < this->p[1].m_width - 1;
                 y++)
              this->lab[y][this->p[0].m_len] = 0;

          for (int z = 0; z < 2; z++) {
            this->p[z].m_width = 0;
            this->p[z].m_len = 0;
          }
        }
}

bool Labyrinth::analyse_Labirint() {
  int counter = 0;

  for (int i = 0; i < this->width; i++)
    for (int j = 0; j < this->len; j++)
      if (this->lab[i][j] == 1)
        counter++;

  if ((int)((counter * 100) / (this->len * this->width)) > 25)
    return false;
  else {
    this->way->do_sWay();
    this->way->coppy_lab(this->lab);
    return true;
  }
}

Labyrinth::~Labyrinth() {
  for (int i = 0; i < this->width; i++)
    delete this->lab[i];

  delete this->lab;
}

void Labyrinth::clear() {
  for (int i = 0; i < this->width; i++)
    delete this->lab[i];

  delete this->lab;
}

void odapte_way(List &bot_way, int swidth, int slen) {
  float *arr_x = new float[bot_way.head->n],
        *arr_z = new float[bot_way.head->n];
  int counter = 1, c = bot_way.head->n;

  arr_z[0] = swidth, arr_x[0] = slen;

  while (bot_way.head != NULL) {
    arr_x[counter] = bot_way.head->m_lval - 1 + visual_Labirint::kx / 6;
    arr_z[counter] = bot_way.head->m_wval - 1 + visual_Labirint::kz / 6;
    bot_way.head = bot_way.head->next;
    counter++;
  }

  visual_Labirint::bot_map_x = arr_x, visual_Labirint::bot_map_z = arr_z;

  visual_Labirint::bot_map_size = c;

  visual_Labirint::bot_position_x = arr_x[counter - 1],
  visual_Labirint::bot_position_z = arr_z[counter - 1];
  visual_Labirint::pointer = counter - 2;
}

void Labyrinth::bot_operation() {
  int **map = new int *[this->width];
  for (int i = 0; i < this->width; i++)
    map[i] = new int[this->len];

  for (int i = 0; i < this->width; i++)
    for (int j = 0; j < this->len; j++)
      if (i != this->start.m_width || j != this->start.m_len)
        map[i][j] = (int)this->lab[i][j];
      else
        map[i][j] = -1;

  List bot_way;

  main_analyzer(map, this->width, this->len, this->end.m_width, this->end.m_len,
                bot_way);

  odapte_way(bot_way, this->start.m_width, this->start.m_len);

  for (int i = 0; i < this->width; i++)
    delete map[i];

  delete map;
}

void Labyrinth::restart() {

  this->regen_Labirint();

  visual_Labirint::width = this->width, visual_Labirint::len = this->len;
  visual_Labirint::delay = this->width * this->len * 20;
  visual_Labirint::start_x = start.m_len,
  visual_Labirint::start_z = start.m_width,
  visual_Labirint::end_z = this->end.m_width,
  visual_Labirint::end_x = this->end.m_len;
  visual_Labirint::Lab_map = this->lab;

  if (visual_Labirint::start_x == 0)
    visual_Labirint::delta_angle = 1.5;

  else if (visual_Labirint::start_x == this->len - 1)
    visual_Labirint::delta_angle = -1.5;

  else if (visual_Labirint::start_z == 0)
    visual_Labirint::delta_angle = 3.0;

  else if (visual_Labirint::start_z == this->width - 1)
    visual_Labirint::delta_angle = 0;

  visual_Labirint::delta_y = 0.0;

  visual_Labirint::position_x = visual_Labirint::start_x - 0.5;
  visual_Labirint::position_z = visual_Labirint::start_z - 0.5;

  this->bot_operation();
}

int Labyrinth::visual(Labyrinth *lab) {
  visual_Labirint::lab = this;

  int argc = 1;
  char *arg = {"Window"};
  char **argv = &arg;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(0, 0);
  glutCreateWindow("Labirint v1.0");
  glutFullScreen();

  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);

  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  glutIgnoreKeyRepeat(1);
  glutKeyboardUpFunc(releaseKey);

  glutSetCursor(GLUT_CURSOR_NONE);
  glutPassiveMotionFunc(processMouse);

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 1;
}