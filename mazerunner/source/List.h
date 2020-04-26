#ifndef H_LIST
#define H_LIST

class List {
public:
  struct node {
    int m_lval, m_wval, n;
    node *next;
  } * head;

  List();
  ~List();

  void add_node(int width, int len);
};

#endif