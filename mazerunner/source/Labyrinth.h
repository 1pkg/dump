#ifndef H_LABIRINT
#define H_LABIRINT

#include "Bot.h"
#include "List.h"
#include "Way.h"

class Labyrinth {
private:
  struct point {
    int m_width, m_len;
  } p[2], start, end;

  bool **lab;

  int len, width;

  Way *way;

public:
  void input_size(int width, int len);
  void clear();
  void restart();

  bool analyse_Labirint();
  void clean_up_Labirint();
  void regen_Labirint();

  int visual(Labyrinth *lab);

  void bot_operation();

  ~Labyrinth();
};

#endif