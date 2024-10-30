#include "Body.h"
bool SnakeBody::operator == (SnakeBody& snakik) {bool q = false;
 if (x == snakik.x && y == snakik.y)  q = true;
 return q;}