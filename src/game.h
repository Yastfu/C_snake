#ifndef _GAME_H
#define _GAME_H

#include "map.h"
#include "snake.h"
#include "constants.h"
#include "input.h"


struct Game{

  struct Map* map;

  struct Snake* snake;

  struct Point* points;
};

struct Game* init();

void update(struct Game* game);

void start(struct Game* game);

void sleep_ms(long ms);

void clear_screen(void);



#endif