#include <stdio.h>
#include <time.h>
#include "game.h"

#define STEP_DELAY_MS 150   // 150 ms entre chaque déplacement
#define SQUARE_SIZE   5     // nombre de pas par côté du carré

void clear_screen(void){
    printf("\033[H\033[J");   // ANSI : replace le curseur en haut et efface l'écran
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

    char directions[4] = { DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_UP };

    while (game->snake->alive){

        for(int side = 0; side < 4 && game->snake->alive; side++){

            for(int step = 0; step < SQUARE_SIZE && game->snake->alive; step++){

                snake_move(directions[side], game->snake);

                if(!game->snake->alive) break;

                update(game);

                clear_screen();
                toString(game->map);

                sleep_ms(STEP_DELAY_MS);
            }
        }
    }

    printf("Le serpent est mort.\n");

    map_free(game->map);
    // pensez à appeler snake_free(game->snake) ici si la fonction existe dans votre code
    free(game);

    return 0;
}