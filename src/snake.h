#ifdef _SNAKE_H
#define _SNAKE_H

#include "constants.h"

struct Snake{

  int size;

  struct* SnakePart;
};

struct SnakePart{

  int width;
  int height;
  
  struct* SnakePart;
};

#endif