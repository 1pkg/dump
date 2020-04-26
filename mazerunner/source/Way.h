#ifndef H_WAY
#define H_WAY

#include "List.h"

class Way : public List {
private:
  int len, width;

public:
  Way(int width, int len);

  bool gate_Checker(int wall, int position);
  void do_Gate();

  bool check_Way(int route, int size);
  void do_step(int route, int size);
  void regen_it();
  bool fin();
  void do_Way();

  void coppy_lab(bool **lab);
  void position(int &start_width, int &start_len, int &end_width, int &end_len);
  void main(bool **labint, int &start_width, int &start_len, int &end_width,
            int &end_len);

  bool check_sWay(int route, int size);
  void do_sWay();

  friend int seed(int distance, int seed);
};

#endif