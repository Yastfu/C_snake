#include "game.h"

int main(void)
{
    struct Game *game = init();

    if (game == NULL){
        printf("Erreur de lancement de la partie\n");
        return 1;
    }

    start(game);

    return 0;
}