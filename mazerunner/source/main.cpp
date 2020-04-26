#include "Labyrinth.h"

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance = NULL, HINSTANCE hPrevInstance = NULL,
                   LPSTR lpCmdLine = NULL, int nCmdShow = NULL) {
  Labyrinth *lab = new Labyrinth();
  lab->visual(lab);
}
