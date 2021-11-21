#include "board.h"
#include "definitions.h"
#include "declarations.h"

#include <stdio.h>

void print_board(const Board* board)
{
    byte index;

    if (!board)
    {
        printf("Null board\n");
        return ;
    }

    index = 0;
    while (index < BOARD_TOTAL_SIZE)
    {
        if (index && (index % BOARD_SIDE_SIZE == 0))
            printf("\n");
     
        printf("%c ", board_at_index(board, index));

        index ++;
    }

    printf("\n\n");
}

void _print_byteP(const byte* byte)
{
    printf("%c ", *byte);
}

void print_index(byte index)
{
    byte row;
    byte col;

    row = index_to_row(index);
    col = index_to_col(index);

    printf("(%d, %d)\n", row, col);
}

void print_separator()
{
    printf("------------------\n");
}