#include "definitions.h"
#include "declarations.h"

int block_ul_positions[BOARD_SIDE_SIZE][2] = 
{
    {0, 0}, {0, 3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {6, 0}, {6, 3}, {6, 6},
};

int get_block_index(byte row, byte col)
{
    return (row / BLOCK_SIDE_SIZE) * BLOCK_SIDE_SIZE + col / BLOCK_SIDE_SIZE;
}

int get_block_indexI(byte cell_index)
{
    return get_block_index(index_to_row(cell_index), index_to_col(cell_index));
}