#include <math.h>
#include <stdlib.h>
#include "pellet.h"
#include "game.h"

#define ZONE_LARGEUR (MAP_WIDTH  - 2)
#define ZONE_HAUTEUR (MAP_HEIGHT - 2)

int pellet_target_count(int casesRestantes){

  double f = (MAX_PELLET * D) / (casesRestantes + D);

  int n = (int)round(f);

  return n > MIN_PELLET ? n : MIN_PELLET;
}

static int is_cell_free(struct Game* game, struct PelletList* pellets, int width, int height){

  char cell = map_get(width, height, game->map);
  if(cell != ' ') return 0;

  struct SnakePart* part = game->snake->snakeHead;
  while(part != NULL){
    if(part->width == width && part->height == height) return 0;
    part = part->nextPart;
  }

  for(int i=0; i<pellets->count; i++){
    if(pellets->width[i] == width && pellets->height[i] == height) return 0;
  }

  return 1;
}

void pellet_spawn_missing(struct Game* game, struct PelletList* pellets){

  int casesRestantes = TOT_CASE - game->snake->size - pellets->count;
  int target = pellet_target_count(casesRestantes);

  if(target > PELLET_LIST_CAPACITY) target = PELLET_LIST_CAPACITY;

  int attempts = 0;
  int maxAttempts = TOT_CASE * 4;

  while(pellets->count < target && attempts < maxAttempts){

    int w = 1 + rand() % ZONE_LARGEUR;
    int h = 1 + rand() % ZONE_HAUTEUR;

    if(is_cell_free(game, pellets, w, h)){
      pellets->width[pellets->count]  = w;
      pellets->height[pellets->count] = h;
      pellets->count++;
    }

    attempts++;
  }
}

void pellet_draw(struct Game* game, struct PelletList* pellets){

  for(int i=0; i<pellets->count; i++){
    map_set(pellets->width[i], pellets->height[i], game->map, FOOD);
  }
}

int pellet_check_eaten(struct Game* game, struct PelletList* pellets){

  int headW = game->snake->snakeHead->width;
  int headH = game->snake->snakeHead->height;

  for(int i=0; i<pellets->count; i++){

    if(pellets->width[i] == headW && pellets->height[i] == headH){

      pellets->width[i]  = pellets->width[pellets->count - 1];
      pellets->height[i] = pellets->height[pellets->count - 1];
      pellets->count--;

      return 1;
    }
  }

  return 0;
}