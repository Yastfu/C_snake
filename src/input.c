#include "input.h"

static struct termios orig_termios;

void input_disable_raw_mode(void){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void input_enable_raw_mode(void){

    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);   // pas d'affichage, pas de buffer ligne par ligne
    raw.c_cc[VMIN]  = 0;               // lecture non-bloquante
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    // rendre stdin non-bloquant également, en complément
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

/* Lit une touche fléchée si disponible, sinon renvoie currentDirection.
   Empêche aussi le demi-tour immédiat (ex: aller à gauche si on va à droite). */
char input_read_direction(char currentDirection){

    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);

    if(n <= 0) return currentDirection;   // rien de lu

    if(c == 27){   // ESC : début possible d'une séquence de touche fléchée

        char seq[2];
        if(read(STDIN_FILENO, &seq[0], 1) <= 0) return currentDirection;
        if(read(STDIN_FILENO, &seq[1], 1) <= 0) return currentDirection;

        if(seq[0] == '['){

            switch(seq[1]){
                case 'A':   // flèche haut
                    if(currentDirection != DIR_DOWN) return DIR_UP;
                    break;
                case 'B':   // flèche bas
                    if(currentDirection != DIR_UP) return DIR_DOWN;
                    break;
                case 'C':   // flèche droite
                    if(currentDirection != DIR_LEFT) return DIR_RIGHT;
                    break;
                case 'D':   // flèche gauche
                    if(currentDirection != DIR_RIGHT) return DIR_LEFT;
                    break;
            }
        }
    }

    return currentDirection;
}