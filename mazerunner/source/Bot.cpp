#include "Bot.h"

void wave(int **map, int width, int len, int delta) {
  for (int y = 0; y < width; y++)
    for (int x = 0; x < len; x++)
      if (map[y][x] == delta) {
        if (y > 0 && map[y - 1][x] == 1)
          map[y - 1][x] = delta - 1;

        if (y < width - 1 && map[y + 1][x] == 1)
          map[y + 1][x] = delta - 1;

        if (x < len - 1 && map[y][x + 1] == 1)
          map[y][x + 1] = delta - 1;

        if (x > 0 && map[y][x - 1] == 1)
          map[y][x - 1] = delta - 1;
      }
}

void main_analyzer(int **map, int width, int len, int fin_width, int fin_len,
                   List &way) {
  int delta = -1;

  do {
    wave(map, width, len, delta);
    delta--;
  } while (map[fin_width][fin_len] == 1);

  restore(map, width, len, delta, fin_width, fin_len, way);
}

void restore(int **map, int width, int len, int delta, int fin_width,
             int fin_len, List &answer) {

  answer.add_node(fin_width, fin_len);
  do {
    if (fin_width > 0 && map[fin_width - 1][fin_len] == delta) {
      answer.add_node(--fin_width, fin_len);
      continue;
    }

    if (fin_width < width - 1 && map[fin_width + 1][fin_len] == delta) {
      answer.add_node(++fin_width, fin_len);
      continue;
    }

    if (fin_len > 0 && map[fin_width][fin_len - 1] == delta) {
      answer.add_node(fin_width, --fin_len);
      continue;
    }

    if (fin_len < len - 1 && map[fin_width][fin_len + 1] == delta) {
      answer.add_node(fin_width, ++fin_len);
      continue;
    }
    delta++;
  } while (delta < 0);
}