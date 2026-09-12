#include <stdio.h>
#include "game.h"

int main(void)
{

    struct Game *game = init();

    if (game == NULL){
        printf("Erreur de lancement de la partie\n");
        return 1;
    }

    toString(game->map);

    printf("Element a la position 0 0 doit afficher + : %c\n", get_info(0,0, game->map));

    printf("Element a la position 0 5 doit afficher | : %c\n", get_info(0,5, game->map));

    printf("Element a la position 5 0 doit afficher - : %c\n", get_info(5,0, game->map));

    printf("Element a la position 5 5 doit afficher   : %c\n", get_info(5,5, game->map));

    return 0;
}
