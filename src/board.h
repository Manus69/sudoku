#ifndef BOARD_H
#define BOARD_H

#include "why_lib.h"

struct Board
{
    byte*   cells;
    byte    empty_cell_count;
};

#endif