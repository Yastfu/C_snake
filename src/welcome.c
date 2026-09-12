#include <stdio.h>
#include "welcome.h"

static const char* welcome_lines[] = {
    "+--------------------------------------------------+",
    "|                                                  |",
    "|                                                  |",
    "|       ####  #   #   ###   #   # #####            |",
    "|       #     ##  #  #   #  #  #  #                |",
    "|        ###  # # #  #####  ###   ####             |",
    "|           # #  ##  #   #  #  #  #                |",
    "|       ####  #   #  #   #  #   # #####            |",
    "|                                                  |",
    "|                TERMINAL EDITION                  |",
    "|                                                  |",
    "|                @oooooo.......*                   |",
    "|                                                  |",
    "|          Appuyez sur les touches fleches         |",
    "|             pour controlre le serpent            |",
    "|                                                  |",
    "|                                                  |",
    "|                                                  |",
    "|                                                  |",
    "+--------------------------------------------------+"
};

#define WELCOME_LINE_COUNT (sizeof(welcome_lines) / sizeof(welcome_lines[0]))

static const char* gameover_lines[] = {
    "+--------------------------------------------------+",
    "|                                                  |",
    "|                                                  |",
    "|   ####    #####  #   #  #####                    |",
    "|  #        #   #  ## ##  #                        |",
    "|  #  ###   #####  # # #  ####                     |",
    "|  #    #   #   #  #   #  #                        |",
    "|   ####    #   #  #   #  #####                    |",
    "|                                                  |",
    "|    ###   #   #  #####  #####                     |",
    "|   #   #  #   #  #      #   #                     |",
    "|   #   #   # #   ####   #####                     |",
    "|   #   #    #    #      #   #                     |",
    "|    ###     #    #####  #   #                     |",
    "|                                                  |"
};

#define GAMEOVER_LINE_COUNT (sizeof(gameover_lines) / sizeof(gameover_lines[0]))

void welcome_show(void){

    for(size_t i = 0; i < WELCOME_LINE_COUNT; i++){
        printf("%s\n", welcome_lines[i]);
    }
}

void gameover_show(int score){

    for(size_t i = 0; i < GAMEOVER_LINE_COUNT; i++){
        printf("%s\n", gameover_lines[i]);
    }

    printf("|                Score : %-4d                      |\n", score);
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("+--------------------------------------------------+\n");
}