#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdbool.h>
#include "constants.h"
#include <stdlib.h>

struct Snake{

  int size;
  char direction;
  bool alive;
  bool justGrew;

  struct SnakePart* snakeHead;

  int prevTailHeight;
  int prevTailWidth;
};

struct SnakePart{

  int width;
  int height;
  char part;
  
  struct SnakePart* nextPart;
};

struct Snake* snake_create();

void snake_kill(struct Snake* snake);

void snake_move(char dir, struct Snake* snake);

void snake_dequeu(struct Snake* snake);

void snake_grow(struct Snake* snake); 

void snake_free(struct Snake* snake);


#endif