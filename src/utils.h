#ifndef __UTILS_H__
#define __UTILS_H__

#include <termios.h>
#include <stdio.h>

#define WEST 1
#define NORTH 2
#define EAST 3
#define SOUTH 4

const int config[3][3] = {
  {9, 9, 10}, {16, 16, 40}, {30, 16, 99}
};

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo);
void resetTermios();
char getch_(int echo);

#endif
