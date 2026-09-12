#ifndef _GAME_H
#define _GAME_H

#include "map.h"
#include "snake.h"
#include "constants.h"


struct Game{

  struct Map *map;

  struct Snake *snake;
};

struct Game* init();

void start();

#endif