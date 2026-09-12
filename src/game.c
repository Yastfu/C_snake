#include <stdlib.h>
#include "game.h"

struct Game* init() {

  struct Game* currentGame = malloc(sizeof(struct Game));
  if(currentGame == NULL) return NULL;

  currentGame->map = map_create();
  currentGame->snake = NULL;

  return currentGame;
}

void start(){
  //TODO : Implementer la logique de démarrage du jeu
}