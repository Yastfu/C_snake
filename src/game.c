#include <stdlib.h>
#include "game.h"

struct Game* init() {

  struct Game* currentGame = malloc(sizeof(struct Game));
  if(currentGame == NULL) return NULL;

  currentGame->map = map_create();
  if(currentGame->map == NULL) return NULL;

  currentGame->snake = snake_create();
  if(currentGame->snake == NULL) return NULL;

  return currentGame;
}


void update(struct Game* game){

  if(game == NULL) return;

  if(!game->snake->justGrew){
    set(game->snake->prevTailWidth, game->snake->prevTailHeight, game->map, ' ');
  }

  struct SnakePart* currentPart = game->snake->snakeHead;

  while(currentPart->nextPart != NULL){

    set(currentPart->width, currentPart->height, game->map, currentPart->part);

    currentPart = currentPart->nextPart;
  }

  set(currentPart->width, currentPart->height, game->map, currentPart->part);
}

void start(){
  //TODO : Implementer la logique de démarrage du jeu
}