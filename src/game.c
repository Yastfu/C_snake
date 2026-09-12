#include "game.h"
#include "pellet.h"
#include <time.h>

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
    map_set(game->snake->prevTailWidth, game->snake->prevTailHeight, game->map, ' ');
  }

  struct SnakePart* currentPart = game->snake->snakeHead;

  while(currentPart->nextPart != NULL){

    map_set(currentPart->width, currentPart->height, game->map, currentPart->part);

    currentPart = currentPart->nextPart;
  }

  map_set(currentPart->width, currentPart->height, game->map, currentPart->part);
}

void start(struct Game* game){

  srand(time(NULL));

  input_enable_raw_mode();
  atexit(input_disable_raw_mode);

  struct PelletList pellets = { .count = 0 };

  char direction = DIR_RIGHT;

  while (game->snake->alive){

    direction = input_read_direction(direction);

    snake_move(direction, game->snake);

    if(!game->snake->alive) break;

    if(pellet_check_eaten(game, &pellets)){
      snake_grow(game->snake);
    }

    pellet_spawn_missing(game, &pellets);

    update(game);
    pellet_draw(game, &pellets);

    clear_screen();
    toString(game->map);

    sleep_ms(STEP_DELAY_MS);
  }

  printf("Le serpent est mort. Score : %d\n", game->snake->size - 2);

  map_free(game->map);
  snake_free(game->snake);
  free(game);
}

void sleep_ms(long ms){
    struct timespec ts;
    ts.tv_sec  = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

void clear_screen(void){
    printf("\033[H\033[J");
}