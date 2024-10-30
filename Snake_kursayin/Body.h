#pragma once
class SnakeBody { public:
  int x;  int y;
  SnakeBody();  ~SnakeBody();
    bool operator == (SnakeBody&);
};