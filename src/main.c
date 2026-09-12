#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"

#define STEP_DELAY_MS 150

void clear_screen(void){
    printf("\033[H\033[J");
}

void sleep_ms(long ms){
    struct timespec ts;
    ts.tv_sec  = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

int main(void)
{
    struct Game *game = init();

    if (game == NULL){
        printf("Erreur de lancement de la partie\n");
        return 1;
    }

    input_enable_raw_mode();
    atexit(input_disable_raw_mode);   // remet le terminal normal, même en cas de sortie brutale

    char direction = DIR_RIGHT;   // direction de départ

    while (game->snake->alive){

        direction = input_read_direction(direction);

        snake_move(direction, game->snake);

        if(!game->snake->alive) break;

        clear_screen();

        update(game);

        sleep_ms(STEP_DELAY_MS);
    }

    printf("Le serpent est mort.\n");

    map_free(game->map);
    snake_free(game->snake);
    free(game);

    return 0;
}