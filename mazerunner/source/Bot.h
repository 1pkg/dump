#ifndef H_BOT
#define H_BOT

#include "List.h"

#include <vector>

void wave(int **, int, int, int);

void main_analyzer(int **map, int width, int len, int fin_width, int fin_len,
                   List &way);

void restore(int **map, int width, int len, int delta, int fin_width,
             int fin_len, List &way);

#endif