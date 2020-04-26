#include "ColorDeck.hpp"
#include "Format.hpp"
#include "Printer.hpp"
#include "Zoom.hpp"
#include "resource.h"

#include <algorithm>
#include <ctime>
#include <list>
#include <stdlib.h>

const int LENTH_OF_SUPPORT = 30;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ItemProc(HWND hwndDlg, UINT message, WPARAM wParam,
                       LPARAM lParam);
void draw(HWND hWnd);
void choseColor(HWND hwnd, Color &color, bool &fail);
void click(HWND hWnd, int len, int width);
void update(HWND hWnd, int len, int width);
void deteckColor(HWND hWnd, int len, int width);
void writeToFile(HWND hwnd);
void writeToFile(HWND hwnd);
void fill();
void startPlay(HWND hwnd);

enum class WhereAMI {
  PLAY,
  HELP,
  MIXED,
  NOOTHING,
};

Color color;
Color colorFill;
Format format;
HINSTANCE hInst;
bool penExist;
bool isPlay;
Zoom zoom;
ColorDeck helpDeck;
ColorDeck mixedDeck;
ColorDeck playDeck;
time_t timeOfPlay;
WhereAMI me;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {

  WNDCLASS wc = {0};
  MSG msg;
  HWND hWnd;
  hInst = hInstance;
  penExist = true;
  isPlay = false;
  me = WhereAMI::NOOTHING;

  wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = "Wnd";
  wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

  RegisterClass(&wc);
  hWnd = CreateWindow("Wnd", "WinMain", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
                      600, 600, NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, nCmdShow);

  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40002,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40003,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40007,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40008,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40009,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40010,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40011,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40012,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40013,
                 MF_DISABLED | MF_GRAYED);

  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

std::pair<short, short> minSize(int len) {
  short width, heigt = ::ceil(::sqrt(len));
  width = heigt;
  for (;;) {
    if (width * heigt < len) {
      if (width < heigt)
        ++width;
      else
        ++heigt;

      break;
    } else {
      if (width > heigt)
        --width;
      else
        --heigt;
    }
  }

  if (width <= ColorDeck::MIN_SIZE)
    width = ColorDeck::MIN_SIZE + 1;
  if (heigt <= ColorDeck::MIN_SIZE)
    heigt = ColorDeck::MIN_SIZE + 1;

  return std::make_pair(width, heigt);
}

void startPlay(HWND hwnd) {
  helpDeck = zoom.getCurrent();

  int y = 0, x = 0;
  int counter = 0;
  std::for_each(zoom.getCurrent().begin(), zoom.getCurrent().end(),
                [&counter](std::pair<Coordinate, Color> it) { counter++; });
  auto size = minSize(counter);

  mixedDeck = ColorDeck(size.first, size.second);

  std::for_each(helpDeck.begin(), helpDeck.end(),
                [size, &x, &y](std::pair<Coordinate, Color> it) {
                  mixedDeck.setItem(Coordinate(y, x), it.second);
                  y++;
                  if (y == size.second)
                    x++, y = 0;
                });

  color = Color("FFFFFF", "00");
  zoom.getCurrent() = ColorDeck(helpDeck.getLen(), helpDeck.getWidth());
  zoom.update();
  isPlay = true;
  timeOfPlay = ::clock();

  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 0), ID_40006,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 0), ID_40002,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 0), ID_40001,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 0), ID_40005,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 1), ID_40003,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 1), ID_40007,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 2), ID_40009,
                 MF_DISABLED | MF_GRAYED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 2), ID_40010, MF_ENABLED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 2), ID_40011, MF_ENABLED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 2), ID_40012, MF_ENABLED);
  EnableMenuItem(GetSubMenu(GetMenu(hwnd), 2), ID_40013, MF_ENABLED);

  me = WhereAMI::PLAY;
}

void draw(HWND hWnd) {

  const int SIZE = 256;

  char buf[SIZE] = {0};

  HDC hdc = GetDC(hWnd);

  RECT rect;
  GetClientRect(hWnd, &rect);

  Detecter d(rect);

  long x = d.scaleX(zoom.getCurrent().getLen()) * zoom.getCurrent().getLen();
  long y =
      d.scaleY(zoom.getCurrent().getWidth()) * zoom.getCurrent().getWidth();

  HDC memDC = CreateCompatibleDC(hdc);

  HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, x, y);
  DeleteObject(SelectObject(memDC, hMemBmp));

  RECT rectD;
  rectD.top = 0;
  rectD.left = 0;
  rectD.right = x;
  rectD.bottom = y;

  Printer p(zoom.getCurrent(), rectD);
  auto size = p.print(memDC, penExist);

  HDC hdcScaled = CreateCompatibleDC(hdc);
  HBITMAP hbmScaled = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
  DeleteObject(SelectObject(hdcScaled, hbmScaled));

  FillRect(hdc, &rect, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));

  StretchBlt(hdcScaled, 0, 0, rect.right, rect.bottom - LENTH_OF_SUPPORT, memDC,
             0, 0, x, y, SRCCOPY);
  BitBlt(hdc, 0, 0, rect.right, rect.bottom - LENTH_OF_SUPPORT, hdcScaled, 0, 0,
         SRCCOPY);

  TextOut(hdc, 0, rect.bottom - LENTH_OF_SUPPORT, buf,
          sprintf_s(buf, "������: %d", zoom.getCurrent().getLen()));
  TextOut(hdc, 0, rect.bottom - LENTH_OF_SUPPORT / 2, buf,
          sprintf_s(buf, "������: %d", zoom.getCurrent().getWidth()));

  POINT point;
  GetCursorPos(&point);
  update(hWnd, point.x, point.y);

  DeleteDC(memDC);
  DeleteDC(hdcScaled);
  DeleteObject(hMemBmp);
  DeleteObject(hbmScaled);

  ReleaseDC(hWnd, hdc);
}

void choseColor(HWND hwnd, Color &color, bool &fail) {
  const int SIZE = 16;

  CHOOSECOLOR cc;
  static COLORREF acrCustClr[SIZE];
  static DWORD rgbCurrent;

  ZeroMemory(&cc, sizeof(CHOOSECOLOR));
  cc.lStructSize = sizeof(CHOOSECOLOR);
  cc.hwndOwner = hwnd;
  cc.lpCustColors = (LPDWORD)acrCustClr;
  cc.rgbResult = color.getMask() >> 8;
  cc.Flags = CC_FULLOPEN | CC_RGBINIT;

  if (ChooseColor(&cc)) {
    fail = false;
    color.changeColor(cc.rgbResult << 8);
  }
}

void click(HWND hWnd, int len, int width) {
  RECT rect;
  GetClientRect(hWnd, &rect);
  rect.bottom -= LENTH_OF_SUPPORT;
  Detecter d(rect);
  Coordinate index = d.click(zoom.getCurrent().getLen(),
                             zoom.getCurrent().getWidth(), len, width);
  if (index.x != SHRT_MAX * -1 && index.y != SHRT_MAX * -1) {
    try {
      zoom.getCurrent().setItem(index, color);
    } catch (std::exception) {
      try {
        if (Color::isWhite(color)) {
          try {
            if (me != WhereAMI::PLAY)
              zoom.getCurrent().deleteItem(index);

            else {
              int x = 0, y = 0;

              for (;;) {
                try {
                  mixedDeck.getItem(Coordinate(x, y));
                } catch (...) {
                  mixedDeck.setItem(Coordinate(x, y),
                                    zoom.getCurrent().getItem(index));
                  zoom.getCurrent().deleteItem(index);
                  break;
                }
                x++;
                if (mixedDeck.getLen() == x)
                  y++, x = 0;
              }
            }
          } catch (std::exception) {
          }
        } else {

          try {
            if (me != WhereAMI::PLAY)
              zoom.getCurrent().getItem(index) = color;
            else {
              int x = 0, y = 0;

              for (;;) {
                try {
                  mixedDeck.getItem(Coordinate(x, y));
                } catch (...) {
                  mixedDeck.setItem(Coordinate(x, y),
                                    zoom.getCurrent().getItem(index));
                  zoom.getCurrent().getItem(index) = color;
                  break;
                }
                x++;
                if (mixedDeck.getLen() == x)
                  y++, x = 0;
              }
            }
          } catch (std::exception) {
          }
        }
      } catch (std::exception) {
      }
    }
  }
}

void update(HWND hWnd, int len, int width) {
  const int SIZE = 16;
  const int SIZES = 255;

  char buf[SIZE] = {0};
  char buffer[SIZES] = {0};

  RECT rect;
  GetClientRect(hWnd, &rect);
  rect.bottom -= LENTH_OF_SUPPORT;
  Detecter d(rect);
  Coordinate index = d.click(zoom.getCurrent().getLen(),
                             zoom.getCurrent().getWidth(), len, width);

  GetClientRect(hWnd, &rect);
  RECT temp;
  temp.bottom = rect.bottom;
  temp.left = rect.right / 2;
  temp.right = rect.right;
  temp.top = rect.bottom - LENTH_OF_SUPPORT;

  GetClientRect(hWnd, &rect);

  HDC hdc = GetDC(hWnd);
  if (index.x != SHRT_MAX * -1 && index.y != SHRT_MAX * -1) {
    FillRect(hdc, &temp, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
    DrawText(hdc, buf, sprintf_s(buf, "%d", index.x + 1), &temp, DT_RIGHT);
    temp.top += LENTH_OF_SUPPORT / 2;
    DrawText(hdc, buf, sprintf_s(buf, "%d", index.y + 1), &temp, DT_RIGHT);

    temp.left = rect.left;

    if (me != WhereAMI::NOOTHING)
      DrawText(hdc, buffer,
               sprintf_s(buffer, "time: %d second",
                         (::clock() - timeOfPlay) / CLOCKS_PER_SEC),
               &temp, DT_CENTER);
  }
  ReleaseDC(hWnd, hdc);
}

Zoom::ZOOM_STAGE getStage(HWND hWnd, int len, int width) {

  RECT rect;
  GetClientRect(hWnd, &rect);
  rect.bottom -= LENTH_OF_SUPPORT;
  Detecter d(rect);
  Coordinate index = d.click(zoom.getCurrent().getLen(),
                             zoom.getCurrent().getWidth(), len, width);

  if (index.y <= zoom.getCurrent().getLen() / 2 &&
      index.x <= zoom.getCurrent().getWidth() / 2)
    return Zoom::ZOOM_STAGE::LEFT_TOP;
  else if (index.y > zoom.getCurrent().getLen() / 2 &&
           index.x <= zoom.getCurrent().getWidth() / 2)
    return Zoom::ZOOM_STAGE::RIGHT_TOP;
  else if (index.y <= zoom.getCurrent().getLen() / 2 &&
           index.x > zoom.getCurrent().getWidth() / 2)
    return Zoom::ZOOM_STAGE::LEFT_BOTTOM;
  else
    return Zoom::ZOOM_STAGE::RIGHT_BOTTOM;
}

void deteckColor(HWND hWnd, int len, int width) {
  RECT rect;
  GetClientRect(hWnd, &rect);
  rect.bottom -= LENTH_OF_SUPPORT;
  Detecter d(rect);
  Coordinate index = d.click(zoom.getCurrent().getLen(),
                             zoom.getCurrent().getWidth(), len, width);
  if (index.x != SHRT_MAX * -1 && index.y != SHRT_MAX * -1) {
    try {
      color = zoom.getCurrent().getItem(index);
    } catch (std::exception) {
      color = Color("FFFFFF", "00");
    }
  }
}

void writeToFile(HWND hwnd) {
  const int SIZE = 256;

  OPENFILENAME ofn;
  char szFile[SIZE] = {0};

  ZeroMemory(&ofn, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hwnd;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = ".xml\0*.xml\0.png\0*.png\0.jpeg\0*.jpeg\0.jpg\0*.jpg\0."
                    "tiff\0*.tiff\0.bmp\0*.bmp\0\0";
  ofn.nFilterIndex = 0;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrDefExt = "xml";
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

  if (GetSaveFileName(&ofn)) {

    try {
      format.writeFile(std::string(ofn.lpstrFile), zoom.getCurrent());
    } catch (std::exception) {
    }
  }
}

void readFromFile(HWND hwnd) {
  const int SIZE = 256;

  OPENFILENAME ofn;
  char szFile[SIZE] = {0};

  ZeroMemory(&ofn, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hwnd;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = ".xml\0*.xml\0.png\0*.png\0.jpeg\0*.jpeg\0.jpg\0*.jpg\0."
                    "tiff\0*.tiff\0.bmp\0*.bmp\0\0";
  ofn.nFilterIndex = 0;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if (GetOpenFileName(&ofn)) {

    try {
      format.readFile(std::string(ofn.lpstrFile), zoom.getCurrent());
      zoom.update();
      EnableMenuItem(GetSubMenu(GetMenu(hwnd), 0), ID_40002, MF_ENABLED);
      EnableMenuItem(GetSubMenu(GetMenu(hwnd), 1), ID_40003, MF_ENABLED);
      EnableMenuItem(GetSubMenu(GetMenu(hwnd), 1), ID_40007, MF_ENABLED);
      EnableMenuItem(GetSubMenu(GetMenu(hwnd), 1), ID_40008, MF_ENABLED);
      EnableMenuItem(GetSubMenu(GetMenu(hwnd), 2), ID_40009, MF_ENABLED);
    } catch (std::exception) {
    }
  }
}

void fill() {
  Coordinate index;
  for (int i = 0; i < zoom.getCurrent().getWidth(); i++)
    for (int j = 0; j < zoom.getCurrent().getLen(); j++) {
      index = Coordinate(i, j);

      try {
        zoom.getCurrent().setItem(index, colorFill);
      } catch (std::exception) {
        try {
          if (Color::isWhite(colorFill)) {
            try {
              zoom.getCurrent().deleteItem(index);
            } catch (std::exception) {
            }
          } else {
            try {
              zoom.getCurrent().getItem(index) = colorFill;
            } catch (std::exception) {
            }
          }
        } catch (std::exception) {
        }
      }
    }
}

BOOL CALLBACK ItemProc(HWND hwndDlg, UINT message, WPARAM wParam,
                       LPARAM lParam) {
  const int SIZE = 16;

  char lenBuf[SIZE] = {0};
  char widBuf[SIZE] = {0};

  switch (message) {
  case WM_COMMAND:
    switch (LOWORD(wParam)) {

    case IDC_BUTTON1:
      GetDlgItemText(hwndDlg, IDC_EDIT1, lenBuf, SIZE);
      GetDlgItemText(hwndDlg, IDC_EDIT2, widBuf, SIZE);

      try {
        zoom.getCurrent() = ColorDeck(atoi(lenBuf), atoi(widBuf));
        zoom.update();
        InvalidateRect(GetParent(hwndDlg), NULL, false);

        EnableMenuItem(GetSubMenu(GetMenu(GetParent(hwndDlg)), 0), ID_40002,
                       MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(GetParent(hwndDlg)), 1), ID_40003,
                       MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(GetParent(hwndDlg)), 1), ID_40007,
                       MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(GetParent(hwndDlg)), 1), ID_40008,
                       MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(GetParent(hwndDlg)), 2), ID_40009,
                       MF_ENABLED);

        EndDialog(hwndDlg, wParam);

      } catch (std::exception) {
        if (ColorDeck::MIN_SIZE >= atoi(lenBuf))
          SetDlgItemText(hwndDlg, IDC_EDIT1, "");
        if (ColorDeck::MIN_SIZE >= atoi(widBuf))
          SetDlgItemText(hwndDlg, IDC_EDIT2, "");
      }
      break;
    case IDC_BUTTON2:
      EndDialog(hwndDlg, wParam);
      return TRUE;

    case WM_DESTROY:
      EndDialog(hwndDlg, wParam);
      return TRUE;
      break;
    }
  }
  return FALSE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                            LPARAM lParam) {

  bool failure = true;

  switch (message) {

  case WM_LBUTTONDOWN:
    if (me != WhereAMI::HELP && me != WhereAMI::MIXED) {

      click(hWnd, LOWORD(lParam), HIWORD(lParam));

      if (me == WhereAMI::PLAY) {
        if (zoom.getCurrent() == helpDeck) {
          const int SIZE = 255;
          char buf[SIZE];

          sprintf_s(buf, "you do it for %d second",
                    (::clock() - timeOfPlay) / CLOCKS_PER_SEC);
          MessageBox(hWnd, buf, "Finish", MB_OK);
          me = WhereAMI::NOOTHING;
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40002, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40005, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40006, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40001, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40003, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40007, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40009, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40008, MF_ENABLED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40010,
                         MF_DISABLED | MF_GRAYED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40011,
                         MF_DISABLED | MF_GRAYED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40012,
                         MF_DISABLED | MF_GRAYED);
          EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40013,
                         MF_DISABLED | MF_GRAYED);
        }

        color = Color("FFFFFF", "00");
      }

      InvalidateRect(hWnd, NULL, false);
    }

  case WM_MOUSEMOVE:
    update(hWnd, LOWORD(lParam), HIWORD(lParam));
    break;

    break;

  case WM_RBUTTONDOWN:
    if (me != WhereAMI::HELP && me != WhereAMI::PLAY) {
      if (HIBYTE(GetKeyState(VK_MENU)) & 0x80) {
        Color temp = color;

        deteckColor(hWnd, LOWORD(lParam), HIWORD(lParam));

        if (Color::isWhite(color) && me == WhereAMI::MIXED)
          color = temp;

        if (me == WhereAMI::MIXED && Color::isWhite(temp)) {
          RECT rect;
          GetClientRect(hWnd, &rect);
          rect.bottom -= LENTH_OF_SUPPORT;
          Detecter d(rect);
          Coordinate index =
              d.click(zoom.getCurrent().getLen(), zoom.getCurrent().getWidth(),
                      LOWORD(lParam), HIWORD(lParam));
          try {
            mixedDeck.deleteItem(index);
          } catch (...) {
          }
          zoom.getCurrent() = mixedDeck;
          InvalidateRect(hWnd, NULL, false);
        }
      } else {
        if (me != WhereAMI::MIXED)
          choseColor(hWnd, color, failure);
      }
    }
    break;

  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case ID_40001:
      if (me == WhereAMI::NOOTHING) {
        readFromFile(hWnd);
        InvalidateRect(hWnd, NULL, false);
      }
      break;

    case ID_40002:
      if (me == WhereAMI::NOOTHING)
        writeToFile(hWnd);
      break;

    case ID_40003:
      if (me == WhereAMI::NOOTHING) {
        zoom.getCurrent().clear();
        InvalidateRect(hWnd, NULL, false);
      }
      break;

    case ID_40006:
      if (me == WhereAMI::NOOTHING) {
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ItemProc);
      }
      break;

    case ID_40007:
      if (me == WhereAMI::NOOTHING) {
        choseColor(hWnd, colorFill, failure);
        if (!failure) {
          fill();
          InvalidateRect(hWnd, NULL, false);
        }
      }
      break;

    case ID_40008:
      if (penExist)
        penExist = false;
      else
        penExist = true;

      InvalidateRect(hWnd, NULL, false);
      break;

    case ID_40004:
      PostQuitMessage(0);
      break;

    case ID_40009:
      if (me == WhereAMI::NOOTHING && !zoom.getCurrent().empty()) {
        startPlay(hWnd);
        InvalidateRect(hWnd, NULL, false);
      }
      break;
    case ID_40010:
      if (me == WhereAMI::PLAY) {
        while (zoom.zoomDown())
          ;
        playDeck = zoom.getCurrent();
      }
      if (me != WhereAMI::NOOTHING) {
        zoom.getCurrent() = helpDeck;
        zoom.update();
        me = WhereAMI::HELP;
        InvalidateRect(hWnd, NULL, false);
      }

      break;
    case ID_40011:
      if (me == WhereAMI::PLAY) {
        while (zoom.zoomDown())
          ;
        playDeck = zoom.getCurrent();
      }
      if (me != WhereAMI::NOOTHING) {
        zoom.getCurrent() = mixedDeck;
        zoom.update();
        me = WhereAMI::MIXED;
        InvalidateRect(hWnd, NULL, false);
      }
      break;
    case ID_40012:
      if (me != WhereAMI::PLAY && me != WhereAMI::NOOTHING) {
        zoom.getCurrent() = playDeck;
        zoom.update();
        me = WhereAMI::PLAY;
        InvalidateRect(hWnd, NULL, false);
      }
      break;
    case ID_40013:
      if (me != WhereAMI::NOOTHING) {
        zoom.getCurrent() = helpDeck;
        zoom.update();
        me = WhereAMI::NOOTHING;
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40002, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40005, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40006, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), ID_40001, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40003, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40007, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40009, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), ID_40008, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40010,
                       MF_DISABLED | MF_GRAYED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40011,
                       MF_DISABLED | MF_GRAYED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40012,
                       MF_DISABLED | MF_GRAYED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_40013,
                       MF_DISABLED | MF_GRAYED);
        InvalidateRect(hWnd, NULL, false);
      }
      break;
    }
    break;

  case WM_PAINT:
    if (zoom.getCurrent().getLen() && zoom.getCurrent().getWidth())
      draw(hWnd);
    else {
      RECT rect;
      GetClientRect(hWnd, &rect);
      HDC hdc = GetDC(hWnd);
      FillRect(hdc, &rect, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
    }
    ValidateRect(hWnd, NULL);
    break;

  case WM_MOUSEWHEEL:

    if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
      zoom.zoomDown();
    else {
      try {

        POINT p;
        p.x = LOWORD(lParam);
        p.y = HIWORD(lParam);
        ScreenToClient(hWnd, &p);

        zoom.zoomUp(getStage(hWnd, p.x, p.y));
      } catch (std::exception) {
      }
    }

    InvalidateRect(hWnd, NULL, false);

    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}
