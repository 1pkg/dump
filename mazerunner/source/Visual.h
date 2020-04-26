#ifndef H_VISUAL
#define H_VISUAL

#include "Labyrinth.h"

namespace visual_Labirint {
extern int windowsizex, windowsizey, width, len;

extern float delta_angle, delta_x, delta_z, delta_y;
extern int keys_Sm[2];
extern bool veto[4];

extern float position_x, position_z, bot_position_x, bot_position_z;

extern int start_x, start_z, end_x, end_z;

extern bool **Lab_map;

extern float const kx;
extern float const ky;
extern float const kz;
extern float const step_k;

extern bool restart_flag, flag_of_input, pause_flag, help_flag;

extern float *bot_map_x, *bot_map_z;
extern int bot_map_size, pointer;

extern int g_pause, delay;

extern Labyrinth *lab;

extern void *font;
} // namespace visual_Labirint

void changeSize(int w, int h);

void renderScene();

void start_finish();
void pause();
void help();
void fps();

void main_fizik();
void computePosition();
void bot_posit();

void releaseKey(unsigned char key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void processMouse(int x, int y);

int royal_vvod();
void input();

bool restart();
void end();

#endif