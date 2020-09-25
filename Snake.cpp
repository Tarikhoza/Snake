#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;

int maxx = 40;
int maxy = 40;

class position {
 public:
  int x = 0;
  int y = 0;
};

class bodyPart {
 public:
  position pos;
  bodyPart(int posx, int posy) {
    pos.x = posx;
    pos.y = posy;
  }
};

class apple {
 public:
  position pos;
  void setPosition() {
    pos.x = rand() % (maxx - 2) + 1;
    pos.y = rand() % (maxy - 2) + 1;
  }

  apple() { setPosition(); }
};

class snake {
 public:
  int len = 1;
  char direction = 'w';
  char lastDirection = 'a';
  bool alive = true;
  vector<bodyPart> body;

  snake() { body.emplace_back(bodyPart((int)maxx/2, (int)maxy/2)); }

  void move() {
    if (direction == 'w') {
      body.insert(body.begin(), bodyPart(body[0].pos.x - 1, body[0].pos.y));
      if (len == body.size() - 1) body.erase(body.begin() + body.size() - 1);
    } else if (direction == 'a') {
      body.insert(body.begin(), bodyPart(body[0].pos.x, body[0].pos.y - 1));
      if (len == body.size() - 1) body.erase(body.begin() + body.size() - 1);
    } else if (direction == 's') {
      body.insert(body.begin(), bodyPart(body[0].pos.x + 1, body[0].pos.y));
      if (len == body.size() - 1) body.erase(body.begin() + body.size() - 1);
    } else if (direction == 'd') {
      body.insert(body.begin(), bodyPart(body[0].pos.x, body[0].pos.y + 1));
      if (len == body.size() - 1) body.erase(body.begin() + body.size() - 1);
    }
  }

  bool eat(apple Apple) {
    if (Apple.pos.x == body[0].pos.x and Apple.pos.y == body[0].pos.y) {
      len++;
      return 1;
    }
    return 0;
  }

  void lose() {
    if (body[0].pos.x <= 0 or body[0].pos.x >= maxx - 1) {
      alive = false;
    }
    if (body[0].pos.y <= 0 or body[0].pos.y >= maxy - 1) {
      alive = false;
    }
    for (int i = 0; i < body.size(); i++) {
      for (int j = 0; j < body.size(); j++) {
        if (i != j) {
          if (body[i].pos.x == body[j].pos.x and
              body[i].pos.y == body[j].pos.y) {
            alive = false;
            break;
            break;
          }
        }
      }
    }
  }

  void changeDirection(char newDirection) {
    if (newDirection == 'w' or newDirection == 'a' or newDirection == 's' or
        newDirection == 'd') {
      if (direction == 'w' and newDirection != 's')
        direction = newDirection;
      else if (direction == 's' and newDirection != 'w')
        direction = newDirection;
      else if (direction == 'a' and newDirection != 'd')
        direction = newDirection;
      else if (direction == 'd' and newDirection != 'a')
        direction = newDirection;
    }
  }

  void control() {
    if (kbhit()) changeDirection(getch());
  }
};

void printDisplay(snake Snake, apple Apple) {
  char print = ' ';
  system("cls");
  for (int i = 0; i < maxx; i++) {
    for (int j = 0; j < maxy; j++) {
      print = ' ';
      for (auto b : Snake.body) {
        if (b.pos.x == i and b.pos.y == j) {
          print = 'O';
          break;
        }
      }
      if (Apple.pos.x == i and Apple.pos.y == j) print = '@';
      if (i == 0 or i == maxx - 1 or j == 0 or j == maxy - 1) print = '#';
      cout << print;
    }
    cout << endl;
  }
  Sleep(120);
}

void game() {
  snake Snake;
  Snake.len = 1;
  apple Apple;
  srand(time(0));
  cin.get();
  while (Snake.alive) {
    printDisplay(Snake, Apple);
    Snake.move();
    Snake.lose();
    if (Snake.eat(Apple)) {
      Apple.setPosition();
    }
    Snake.control();
  }
  cout << "Your score is " << Snake.len << endl;
}

int main() {
  cout.sync_with_stdio(false);
  game();
}
