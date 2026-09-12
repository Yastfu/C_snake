#ifndef _PELLET_H
#define _PELLET_H

#include "game.h"

#define PELLET_LIST_CAPACITY MAX_PELLET

struct PelletList{

  int width[PELLET_LIST_CAPACITY];
  int height[PELLET_LIST_CAPACITY];

  int count;
};

int  pellet_target_count(int casesRestantes);

void pellet_spawn_missing(struct Game* game, struct PelletList* pellets);

void pellet_draw(struct Game* game, struct PelletList* pellets);

int  pellet_check_eaten(struct Game* game, struct PelletList* pellets);

#endif