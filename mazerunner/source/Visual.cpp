#include "Visual.h"

#include <Windows.h>
#include <glut.h>
#include <math.h>
#include <time.h>

namespace visual_Labirint {
int windowsizex, windowsizey, width, len;

float delta_angle, delta_x = 0.0f, delta_z = 0.0f, delta_y = 0.0f;
int keys_Sm[2] = {0, 0};
bool veto[4] = {0, 0, 0, 0};

float position_x, position_z, bot_position_x, bot_position_z;

int start_x, start_z, end_x, end_z;

bool **Lab_map;

float const kx = 3.0;
float const ky = 3.0;
float const kz = 3.0;
float const step_k = 0.03f;

bool restart_flag = 0, flag_of_input = 1, pause_flag = 0, help_flag = 0;

float *bot_map_x, *bot_map_z;
int bot_map_size, pointer;

int g_pause = 0, delay = 0;

Labyrinth *lab;

void *font = GLUT_BITMAP_HELVETICA_18;
} // namespace visual_Labirint

using namespace visual_Labirint;

void changeSize(int w, int h) {

  if (h == 0)
    h = 1;

  float ratio = w * 1.0 / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);

  windowsizex = w;
  windowsizey = h;
}

bool restart() {
  while (1) {
    if (GetAsyncKeyState(89) < 0)
      return true;
    else if (GetAsyncKeyState(78) < 0)
      return false;
  }
}

void end(bool flag) {
  char *string;
  int i = 0;
  float deltax = 0.0;

  if (flag == 1) {
    string = "Player Win.";

    for (int i = 0; i < 6; i++)
      deltax -= glutBitmapWidth(font, string[i]);
  } else {
    string = "Bot Win.";

    for (int i = 0; i < 3; i++)
      deltax -= glutBitmapWidth(font, string[i]);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, windowsizex, windowsizey, 0);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1.0f, 1.0f, 1.0f);

  glPushMatrix();
  while (string[i] != '\0') {
    glRasterPos2f(windowsizex / 2 + deltax, windowsizey / 2);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i++;
  }
  glPopMatrix();

  glutSwapBuffers();
  Sleep(3000);

  string = "Do you wanna restart Y/N?";
  i = 0, delta_x = 0.0;

  for (int i = 0; i < 13; i++)
    deltax -= glutBitmapWidth(font, string[i]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
  while (string[i] != '\0') {
    glRasterPos2f(windowsizex / 2 + deltax, windowsizey / 2);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i++;
  }
  glPopMatrix();

  glutSwapBuffers();

  if (restart()) {
    lab->clear();
    flag_of_input = 1;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
  } else {
    lab->clear();
    exit(0);
  }
}

void start_finish() {
  char *string = "Start";
  int i = 0;

  glColor3f(1.0f, 1.0f, 1.0f);

  glPushMatrix();
  glRasterPos3f((start_x - 0.5) * kx, ky / 2, (start_z - 0.5) * kz);
  while (string[i] != '\0') {
    glutBitmapCharacter(font, string[i]);
    i++;
  }
  glPopMatrix();

  i = 0, string = "End";

  glPushMatrix();
  glRasterPos3f((end_x - 0.5) * kx, ky / 2, (end_z - 0.5) * kz);
  while (string[i] != '\0') {
    glutBitmapCharacter(font, string[i]);
    i++;
  }
  glPopMatrix();
}

void pause() {
  char *string = "Pause";
  int i = 0;
  float deltax = 0.0;

  for (int i = 0; i < 2; i++)
    deltax -= glutBitmapWidth(font, string[i]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, windowsizex, windowsizey, 0);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1.0f, 1.0f, 1.0f);

  glPushMatrix();
  while (string[i] != '\0') {
    glRasterPos2f(windowsizex / 2 + deltax, windowsizey / 2);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i++;
  }
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glutSwapBuffers();
}

void help() {
  char *string = "To move use WASD";
  int i = 0;
  float deltax = 0.0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, windowsizex, windowsizey, 0);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1.0f, 1.0f, 1.0f);

  glPushMatrix();
  while (string[i] != '\0') {
    glRasterPos2f(deltax, 18);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i++;
  }

  string = "To restart use Tab", i = 0, deltax = 0.0;

  while (string[i] != '\0') {
    glRasterPos2f(deltax, 18 * 2);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i++;
  }

  string = "To exit use Esc", i = 0, deltax = 0.0;

  while (string[i] != '\0') {
    glRasterPos2f(deltax, 18 * 3);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i++;
  }
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glutSwapBuffers();
}

void fps() {
  static char string[11];
  char *str;
  int i = 0;
  float deltax = 0.0;

  int time;
  static int frame = 0;
  static int timebase = 0;

  frame++;
  time = glutGet(GLUT_ELAPSED_TIME);

  if (time - timebase > 1000) {
    sprintf(string, "FPS   : %d", frame);
    timebase = time;
    frame = 0;
  }

  while (string[i] != '\0') {
    deltax += glutBitmapWidth(font, string[i]);
    i++;
  }

  deltax = 18;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, windowsizex, windowsizey, 0);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1.0f, 1.0f, 1.0f);

  glPushMatrix();
  while (i >= 0) {
    glRasterPos2f(windowsizex - deltax, 18);
    deltax += glutBitmapWidth(font, string[i]);
    glutBitmapCharacter(font, string[i]);
    i--;
  }

  str = "Use F1 to help", i = 0, deltax = 0.0;

  while (str[i] != '\0') {
    glRasterPos2f(deltax, 18);
    deltax += glutBitmapWidth(font, str[i]);
    glutBitmapCharacter(font, str[i]);
    i++;
  }
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

bool pribliz_ravno_humanv(float posit, float hum_position, float step_k) {
  if (abs(posit - hum_position) <= step_k)
    return true;
  else
    return false;
}

bool pribliz_ravno_botv(float &posit, float bot_position, float step_k) {
  if (abs(posit - bot_position) <= step_k) {
    posit = bot_position;
    return true;
  } else
    return false;
}

float preobraz(float param) {
  if (param > 0) {
    while (param > 1)
      param -= 1;
    return param;
  } else
    return 1 - param;
}

void returner(float smash, bool ind) {
  if (ind && smash <= 0.1)
    veto[3] = 1;
  else if (ind && smash >= 0.9)
    veto[2] = 1;

  if (!ind && smash <= 0.1)
    veto[1] = 1;
  else if (!ind && smash >= 0.9)
    veto[0] = 1;
}

void returner() {
  if (position_x > len - 1.2)
    position_x = len - 1.2;
  else if (position_x < -0.8)
    position_x = -0.8;

  if (position_z > width - 1.2)
    position_z = width - 1.2;
  else if (position_z < -0.8)
    position_z = -0.8;
}

void main_fizik() {
  for (int i = 0; i < 4; i++)
    veto[i] = 0;

  if (position_x > len - 1.2 || position_z > width - 1.2 || position_x < -0.8 ||
      position_z < -0.8)
    returner();

  float smash_x = preobraz(position_x);
  float smash_z = preobraz(position_z);

  if (smash_x <= 0.1) {
    if (Lab_map[(int)(position_z + 1)][(int)(position_x + 1) - 1] == 0)
      returner(smash_x, true);
  } else if (smash_x >= 0.9) {
    if (Lab_map[(int)(position_z + 1)][(int)(position_x + 1) + 1] == 0)
      returner(smash_x, true);
  }

  if (smash_z <= 0.1) {
    if (Lab_map[(int)(position_z + 1) - 1][(int)(position_x + 1)] == 0)
      returner(smash_z, false);
  } else if (smash_z >= 0.9) {
    if (Lab_map[(int)(position_z + 1) + 1][(int)(position_x + 1)] == 0)
      returner(smash_z, false);
  }
}

void bot_posit() {
  if (pointer == 0)
    end(0);
  else {
    if (pribliz_ravno_botv(bot_map_x[pointer], bot_position_x, step_k) &&
        pribliz_ravno_botv(bot_map_z[pointer], bot_position_z, step_k))
      pointer--;

    else if (bot_map_x[pointer] == bot_position_x)
      if (bot_map_z[pointer] - bot_position_z > 0)
        bot_position_z += step_k;
      else
        bot_position_z -= step_k;

    else if (bot_map_x[pointer] - bot_position_x > 0)
      bot_position_x += step_k;
    else
      bot_position_x -= step_k;
  }
}

void computePosition() {
  if (pribliz_ravno_humanv(end_x - 0.5, position_x, 0.3) &&
      pribliz_ravno_humanv(end_z - 0.5, position_z, 0.3))
    end(1);
  else {
    delta_x = sin(delta_angle);
    delta_z = -cos(delta_angle);

    float temp_x = position_x, temp_z = position_z;

    for (int i = 0; i < 2; i++) {
      switch (keys_Sm[i]) {
      case 4:
        temp_x += delta_z * step_k;
        temp_z -= delta_x * step_k;
        break;

      case 3:
        temp_x -= delta_z * step_k;
        temp_z += delta_x * step_k;
        break;

      case 1:
        temp_x += delta_x * step_k;
        temp_z += delta_z * step_k;
        break;

      case 2:
        temp_x -= delta_x * step_k;
        temp_z -= delta_z * step_k;
        break;
      }
    }

    if (temp_x - position_x > 0 && !veto[2])
      position_x = temp_x;
    else if (temp_x - position_x < 0 && !veto[3])
      position_x = temp_x;

    if (temp_z - position_z > 0 && !veto[0])
      position_z = temp_z;
    else if (temp_z - position_z < 0 && !veto[1])
      position_z = temp_z;
  }
}

void pause_time(int &pause, int time) {
  static int t1 = 0;

  if (t1 != 0)
    pause += time - t1;

  t1 = time;
}

void renderScene() {

start:
  if (flag_of_input)
    input();

  else {
    static int l_pause = 0;

    if (!pause_flag) {
      g_pause += l_pause;
      l_pause = 0;

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      computePosition();
      if (flag_of_input)
        goto start;

      main_fizik();

      fps();

      gluLookAt(kx * position_x, 1.0f, kz * position_z,
                kx * position_x + delta_x, 1.0f + (delta_y * ky),
                kz * position_z + delta_z, 0.0f, 1.0f, 0.0f);

      glColor3f(1.0f, 1.0f, 1.0f);

      glPushMatrix();
      glBegin(GL_QUADS);
      glVertex3f((len - 1) * kx, 0.0f, (width - 1) * ky);
      glVertex3f((len - 1) * kx, 0.0f, -ky);
      glVertex3f(-kx, 0.0f, -ky);
      glVertex3f(-kx, 0.0f, (width - 1) * ky);
      glEnd();
      glPopMatrix();

      start_finish();

      float gl_col_r, gl_col_g, gl_col_b;

      if (glutGet(GLUT_ELAPSED_TIME) >= delay + g_pause) {
        bot_posit();
        if (flag_of_input)
          goto start;

        gl_col_r = (rand() % 100) * 0.01, gl_col_g = (rand() % 100) * 0.01,
        gl_col_b = (rand() % 100) * 0.01;
        glColor3f(gl_col_r, gl_col_g, gl_col_b);

        glPushMatrix();
        glTranslated(bot_position_x * kx, 1.0, bot_position_z * kz);
        glutWireSphere(1, 45, 15);
        glPopMatrix();
      }

      for (int i = 0; i < width; i++)
        for (int j = 0; j < len; j++) {

          gl_col_r = 0, gl_col_g = 0, gl_col_b = 0;
          if (j % 2 == 0)
            gl_col_r = 1.0;
          else if (i % 2 == 0)
            gl_col_b = 1.0;
          else
            gl_col_g = 1.0;

          if (Lab_map[i][j] == 0) {

            glColor3f(gl_col_r, gl_col_g, gl_col_b);

            glPushMatrix();
            glBegin(GL_QUADS);
            // up
            glVertex3f(visual_Labirint::kx * (j - 1), visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j - 1), visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            // down
            glVertex3f(visual_Labirint::kx * (j - 1),
                       0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j - 1),
                       0.0f * visual_Labirint::kz, visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), 0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), 0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            // front
            glVertex3f(visual_Labirint::kx * (j - 1), visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j - 1),
                       0.0f * visual_Labirint::kz, visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), 0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            // back
            glVertex3f(visual_Labirint::kx * (j - 1), visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j - 1),
                       0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j), 0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j), visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            // right
            glVertex3f(visual_Labirint::kx * (j), visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), 0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j), 0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j), visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            // left
            glVertex3f(visual_Labirint::kx * (j - 1), visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j - 1),
                       0.0f * visual_Labirint::kz,
                       visual_Labirint::ky * (i - 1));
            glVertex3f(visual_Labirint::kx * (j - 1),
                       0.0f * visual_Labirint::kz, visual_Labirint::ky * (i));
            glVertex3f(visual_Labirint::kx * (j - 1), visual_Labirint::kz,
                       visual_Labirint::ky * (i));

            glEnd();
            glPopMatrix();
          }

          else {
            glPushMatrix();
            glTranslatef(ky, 0, kx);
            glPopMatrix();
          }
        }

      glutSwapBuffers();
    } else {
      if (l_pause == 0) {
        if (!help_flag)
          pause();
        else
          help();
      }

      pause_time(l_pause, glutGet(GLUT_ELAPSED_TIME));
    }
  }
}

void releaseKey(unsigned char key, int x, int y) {

  switch (key) {
  case 'A':
  case 'a':
  case 'D':
  case 'd':
    keys_Sm[1] = 0;
    break;

  case 'W':
  case 'w':
  case 'S':
  case 's':
    keys_Sm[0] = 0;
    break;
  }
}

void processSpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_F1)
    if (help_flag == 1)
      help_flag = 0, pause_flag = 0;
    else
      help_flag = 1, pause_flag = 1;
}

void processNormalKeys(unsigned char key, int x, int y) {

  switch (key) {
  case 27:
    exit(0);
    break;

  case 9:
    lab->clear(), flag_of_input = 1;
    break;

  case 32:
    if (pause_flag == 1)
      help_flag = 0, pause_flag = 0;
    else
      pause_flag = 1;
    break;

  case 'A':
  case 'a':
    keys_Sm[1] = 4;
    break;

  case 'D':
  case 'd':
    keys_Sm[1] = 3;
    break;

  case 'W':
  case 'w':
    keys_Sm[0] = 1;
    break;

  case 'S':
  case 's':
    keys_Sm[0] = 2;
    break;
  }
}

void processMouse(int x, int y) {
  if (!pause_flag && !flag_of_input) {

    if (x > windowsizex / 2) {
      delta_angle += 0.05f;
      glutWarpPointer(windowsizex / 2, windowsizey / 2);
    } else if (x < windowsizex / 2) {
      delta_angle -= 0.05f;
      glutWarpPointer(windowsizex / 2, windowsizey / 2);
    }

    if (y < windowsizey / 2) {
      delta_y += 0.02f;
      glutWarpPointer(windowsizex / 2, windowsizey / 2);
    } else if (y > windowsizey / 2) {
      delta_y -= 0.02f;
      glutWarpPointer(windowsizex / 2, windowsizey / 2);
    }

  } else
    glutWarpPointer(windowsizex / 2, windowsizey / 2);
}

void input() {

  char *string[2] = {"Input len of labyrinth", "Input width of labyrinth"},
       *recomended = "Recomended size from 10 to 100";
  int i = 0, k = 0, size[2];
  float xdelta = 0.0, deltax[2] = {0.0, 0.0};

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 8; j++)
      deltax[i] -= glutBitmapWidth(font, string[i][j]);

  glColor3f(1.0f, 1.0f, 1.0f);

  for (int j = 0; j < 2; j++) {

    for (int z = 0; z < 10; z++)
      xdelta -= glutBitmapWidth(font, recomended[z]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowsizex, windowsizey, 0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    while (string[j][i] != '\0') {
      glRasterPos2f(windowsizex / 2 + deltax[j], windowsizey / 2);
      deltax[j] += glutBitmapWidth(font, string[j][i]);
      glutBitmapCharacter(font, string[j][i]);
      i++;
    }

    while (recomended[k] != '\0') {
      glRasterPos2f(windowsizex / 2 + xdelta, windowsizey / 2 + 18);
      xdelta += glutBitmapWidth(font, recomended[k]);
      glutBitmapCharacter(font, recomended[k]);
      k++;
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    glutPostRedisplay();
    Sleep(2000);

    size[j] = royal_vvod();

    i = 0, k = 0, xdelta = 0.0;
  }

  lab->input_size(size[1], size[0]);
  lab->restart();
  flag_of_input = 0;
}

int royal_vvod() {
  int number[3] = {0, 0, 0}, p = 2, fin_num = 0, i = 0, number_of_key = 0;
  char string[9];
  float deltax = 0.0;
  bool flag_of_end = 0;

  while (1) {

    for (int j = 0; j < 3; j++) {
      if (j == 1)
        fin_num += number[j] * 10;
      else if (j == 2)
        fin_num += number[j] * 100;
      else
        fin_num += number[j];
    }

    sprintf(string, "%d", fin_num);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowsizex, windowsizey, 0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    while (string[i] != '\0') {
      glRasterPos2f(windowsizex / 2 + deltax, windowsizey / 2 + 18);
      deltax += glutBitmapWidth(font, string[i]);
      glutBitmapCharacter(font, string[i]);
      i++;
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();

    if (flag_of_end && fin_num >= 10 && fin_num <= 100)
      break;
    else if (fin_num < 10 || fin_num > 100)
      flag_of_end = 0;

    i = 0, deltax = 0.0, fin_num = 0;

    while (1) {
      if (GetAsyncKeyState(13) & 0x8000) {
        flag_of_end = 1;
        number_of_key = 0;
        break;
      } else if (GetAsyncKeyState(8) < 0 && p < 2 && number[p] == 0 &&
                 number_of_key != 8) {
        number_of_key = 8;
        p++;
        number[p] = 0;
        goto l1;
      } else if (GetAsyncKeyState(8) < 0 && p < 3 && number_of_key != 8) {
        number_of_key = 8;
        number[p] = 0;
        goto l1;
      } else {
        for (int i = 0; i < 10; i++) {
          if (GetAsyncKeyState(48 + i) < 0 && p > 0 &&
              number_of_key != 48 + i) {
            number_of_key = 48 + i;
            number[p] = i, p--;
            goto l1;
          } else if (GetAsyncKeyState(48 + i) < 0 && p == 0 &&
                     number_of_key != 48 + i) {
            number_of_key = 48 + i;
            number[p] = i;
            goto l1;
          }
        }
      }
    }
  l1:
    while (GetAsyncKeyState(number_of_key) != 0) { /*������ � ������ �����*/
    }

    number_of_key = 0;
  }

  return fin_num;
}