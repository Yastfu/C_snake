#ifndef _INPUT_H
#define _INPUT_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "constants.h"

void input_enable_raw_mode(void);

void input_disable_raw_mode(void);

char input_read_direction(char currentDirection);

#endif