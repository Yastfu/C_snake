#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "map.h"


struct Map* map_create(){

  struct Map* map = malloc(sizeof(struct Map));
  if(map == NULL) return NULL;

  map->map = malloc(MAP_HEIGHT * sizeof(char*));
  if(map->map == NULL){
    free(map);
    return NULL;
  }

  for(int y=0; y<MAP_HEIGHT; y++){

    map->map[y] = malloc((MAP_WIDTH + 1) * sizeof(char)); // +1 pour '\0' en fin de ligne
    if(map->map[y] == NULL){
      // libère ce qui a déjà été alloué avant d'échouer
      for(int j=0; j<y; j++) free(map->map[j]);
      free(map->map);
      free(map);
      return NULL;
    }
  }

  for(int y=0; y<MAP_HEIGHT; y++){

    for(int x=0; x<MAP_WIDTH; x++){

      if((y == 0 || y == MAP_HEIGHT-1) && (x == 0 || x == MAP_WIDTH-1)) map->map[y][x] = '+';

      else if(y == 0 || y == MAP_HEIGHT-1) map->map[y][x] = '-';

      else if(x == 0 || x == MAP_WIDTH-1) map->map[y][x] = '|';

      else map->map[y][x] = ' ';
    }

    map->map[y][MAP_WIDTH] = '\0';
  }

  return map;
}

char map_get(int width, int height, struct Map *map)
{

  if(map == NULL || map->map == NULL) return '\0';

  if(height < 0 || height >= MAP_HEIGHT) return '\0';

  if(width < 0 || width >= MAP_WIDTH) return '\0';

  return map->map[height][width];
}

void map_set(int width, int height, struct Map* map, char c){
  
  if(map == NULL || map->map == NULL) return;
  if(height < 0 || height >= MAP_HEIGHT) return;
  if(width < 0 || width >= MAP_WIDTH) return;

  map->map[height][width] = c;
}

void toString(struct Map *map)
{

  if(map == NULL) return;

  for(int y=0; y<MAP_HEIGHT; y++){
    printf("%s\n", map->map[y]);
  }
}

void map_free(struct Map *map)
{
  if(map == NULL) return;

  for(int y=0; y<MAP_HEIGHT; y++){
    free(map->map[y]);
  }
  free(map->map);
  free(map);
}

// +--------------------------------+
// |                                |
// |      @@@@@                     |
// |          @                     |
// |          O                     |
// |                                |
// |                    *           |
// |                                |
// |                                |
// |                                |
// +--------------------------------+