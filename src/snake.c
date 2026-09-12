#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

struct Snake* snake_create(){

  struct Snake* snake = malloc(sizeof(struct Snake));
  if(snake == NULL) return NULL;

  snake->size = 2;
  snake->direction = DIR_LEFT;
  snake->alive = true;
  snake->justGrew = false;

  struct SnakePart* snakeHead = malloc(sizeof(struct SnakePart));
  if(snakeHead == NULL){
    free(snake);
    return NULL;
  }

  struct SnakePart* snakeBody = malloc(sizeof(struct SnakePart));
  if(snakeBody == NULL){
    free(snakeHead);
    free(snake);
    return NULL;
  }

  snakeHead->height = MAP_HEIGHT/2;
  snakeHead->width  = MAP_WIDTH/2;
  snakeHead->part   = SNAKE_HEAD;

  snakeBody->height = snakeHead->height;
  snakeBody->width  = snakeHead->width + 1;
  snakeBody->part   = SNAKE_BODY;
  snakeBody->nextPart = NULL;

  snake->snakeHead = snakeHead;
  snakeHead->nextPart = snakeBody;

  /* la queue actuelle = snakeBody, on initialise sa position "précédente"
     à elle-même : rien à effacer avant le tout premier update() */
  snake->prevTailHeight = snakeBody->height;
  snake->prevTailWidth  = snakeBody->width;

  return snake;
}

void snake_kill(struct Snake* snake){

  snake->alive = false;
}

void snake_move(char dir, struct Snake* snake){

  snake->direction = dir;
  snake->justGrew = false;

  struct SnakePart* tail = snake->snakeHead;
  while(tail->nextPart != NULL){
    tail = tail->nextPart;
  }
  snake->prevTailHeight = tail->height;
  snake->prevTailWidth  = tail->width;

  int oldHeight = snake->snakeHead->height;
  int oldWidth  = snake->snakeHead->width;

  if(snake->direction == DIR_UP){

    if(snake->snakeHead->height <= 1){          // 1 = juste après le mur du haut
      snake_kill(snake);
      return;
    }

    snake->snakeHead->height = snake->snakeHead->height - 1;
  }

  else if(snake->direction == DIR_DOWN){

    if(snake->snakeHead->height >= MAP_HEIGHT - 2){   // juste avant le mur du bas
      snake_kill(snake);
      return;
    }

    snake->snakeHead->height = snake->snakeHead->height + 1;
  }

  else if(snake->direction == DIR_LEFT){

    if(snake->snakeHead->width <= 1){            // juste après le mur de gauche
      snake_kill(snake);
      return;
    }

    snake->snakeHead->width = snake->snakeHead->width - 1;
  }

  else if(snake->direction == DIR_RIGHT){

    if(snake->snakeHead->width >= MAP_WIDTH - 2){     // juste avant le mur de droite
      snake_kill(snake);
      return;
    }

    snake->snakeHead->width = snake->snakeHead->width + 1;
  }

  struct SnakePart* current = snake->snakeHead->nextPart;

  while(current != NULL){

    int tmpHeight = current->height;
    int tmpWidth  = current->width;

    current->height = oldHeight;
    current->width  = oldWidth;

    oldHeight = tmpHeight;
    oldWidth  = tmpWidth;

    current = current->nextPart;
  }
}

void snake_dequeue(struct Snake* snake){

  if(snake->snakeHead == NULL) return;

  struct SnakePart* snakePart = snake->snakeHead;
  struct SnakePart* prevSnakePart = NULL;

  while(snakePart->nextPart != NULL){

    prevSnakePart = snakePart;
    snakePart = snakePart->nextPart;
  }

  free(snakePart);

  snake->size = snake->size - 1;

  if(prevSnakePart == NULL){
    /* c'était le dernier segment restant */
    snake->snakeHead = NULL;
  } else {
    prevSnakePart->nextPart = NULL;
  }
}

void snake_free(struct Snake* snake){

  while(snake->snakeHead != NULL){

    snake_dequeue(snake);
  }

  free(snake);
}