// buffer (char [][])
// read keyboard input
// cursor
// read from file (converting file to our buffer)
// write to file (converting our buffer to a file)
//

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
using namespace std;

const int width = 120;
const int height = 40;
const int FPS = 30;

void clearScreen() { cout << "\033[2J\033[1;1H"; }

class Cursor {
public:
  int x;
  int y;
  Cursor() {
    x = 0;
    y = 0;
  }
};

void draw(char buffer[height][width], Cursor cursor, string mode, string log) {
  for (int i = 0; i < height; i++) {
    cout << '\n';
    for (int j = 0; j < width; j++) {
      if (j == 0) {
        if (i - cursor.y == 0) {
          cout << i;
        } else {
          cout << abs(i - cursor.y);
        }
      }
      if (i == cursor.y && j == cursor.x) {
        cout << '#';
      } else {
        cout << buffer[i][j];
      }
    }
  }

  cout << mode + " MODE\n";
  cout << log;
  cout << '\n';
}
void enableRawMode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO); // disable buffering + echo
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int main() {
  enableRawMode();

  string log;
  char c;

  Cursor cursor;

  string mode = "NORMAL";

  char buffer[height][width];
  char copyLine[width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      buffer[i][j] = ' ';
    }
  }

  while (1) {
    read(STDIN_FILENO, &c, 1);

    if (mode == "INSERT") {
      if (c == 127 || c == 8) { // backspace
        if (cursor.x > 0) {
          cursor.x--;
          buffer[cursor.y][cursor.x] = ' ';
        }
      } else if (c == 27) { // escape
        mode = "NORMAL";
      } else {
        if (cursor.x < width) {
          buffer[cursor.y][cursor.x] = c;
          cursor.x++;
        }
      }
    }

    if (mode == "NORMAL") {
      if (c == 'j') {
        if (cursor.y < height - 1)
          cursor.y++;
      } else if (c == 'k') {
        if (cursor.y > 0)
          cursor.y--;
      } else if (c == 'h') {
        if (cursor.x > 0)
          cursor.x--;
      } else if (c == 'l') {
        if (cursor.x < width - 1)
          cursor.x++;
      } else if (c == 'y') {
        for (int i = 0; i < width; i++) {
          copyLine[i] = buffer[cursor.y][i];
        }
      } else if (c == 'p') {
        for (int i = 0; i < width; i++) {
          buffer[cursor.y][i] = copyLine[i];
        }
      } else if (c == 'i') {
        mode = "INSERT";
      } else if (c == 'v') {
        mode = "VISUAL LINE";
      }
    }
    draw(buffer, cursor, mode, log);
    this_thread::sleep_for(chrono::milliseconds(FPS / 1000));
  }

  return 0;
}
