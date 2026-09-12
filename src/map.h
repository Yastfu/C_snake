#ifndef _MAP_H
#define _MAP_H

#include "constants.h"

struct Map{

  char** map;
};

struct Map* map_create();

char map_get(int width, int height, struct Map* map);

void map_set(int width, int height, struct Map* map, char c);

void map_free(struct Map* map);

void toString(struct Map* map);

#endif