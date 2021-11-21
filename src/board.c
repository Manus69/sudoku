#include "definitions.h"
#include "declarations.h"
#include "board.h"

extern int block_ul_positions[BOARD_SIDE_SIZE][2];

static byte _count_empty_cells(const char* values)
{
    byte count;
    byte index;

    count = 0;
    index = 0;
    while (index < BOARD_TOTAL_SIZE)
    {
        if (values[index] == EMPTY_CELL_SYMBOL)
            count ++;
        
        index ++;
    }

    return count;
}

Board* board_create(const char* values)
{
    Board* board;

    board = allocate(sizeof(Board));
    board->cells = memory_copy(values, BOARD_SIDE_SIZE * BOARD_SIDE_SIZE);
    board->empty_cell_count = _count_empty_cells(values);

    return board;
}

void board_destroy(Board* board)
{
    if (!board)
        return ;
    
    free(board->cells);
    free(board);
}

Board* board_copy(const Board* board)
{
    Board* new_board;

    new_board = allocate(sizeof(Board));
    new_board->cells = memory_copy(board->cells, BOARD_TOTAL_SIZE);
    new_board->empty_cell_count = board->empty_cell_count;

    return new_board;
}

bool board_is_solved(const Board* board)
{
    return board->empty_cell_count == 0;
}

byte index_to_row(byte index)
{
    return index / BOARD_SIDE_SIZE;
}

byte index_to_col(byte index)
{
    return index % BOARD_SIDE_SIZE;
}

byte row_col_to_index(byte row, byte col)
{
    return row * BOARD_SIDE_SIZE + col;
}

void board_set_at_index(Board* board, byte value, byte index)
{
    board->cells[index] = value;
    board->empty_cell_count --;
}

void board_set(Board* board, byte value, byte row, byte col)
{
    board_set_at_index(board, value, row_col_to_index(row, col));
}

byte board_at_index(const Board* board, byte index)
{
    return board->cells[index];
}

byte board_at(const Board* board, byte row, byte col)
{
    return board_at_index(board, row_col_to_index(row, col));
}

byte board_atS(const Board* board, byte col, byte row)
{
    return board_at(board, row, col);
}

bool board_cells_equal(const Board* board, byte row_a, byte col_a, byte row_b, byte col_b)
{
    return board_at(board, row_a, col_a) == board_at(board, row_b, col_b);
}

byte board_cell_is_empty(const Board* board, byte row, byte col)
{
    return board_at(board, row, col) == EMPTY_CELL_SYMBOL ? 1 : 0;
}

byte board_cell_is_nonempty(const Board* board, byte row, byte col)
{
    return !board_cell_is_empty(board, row, col);
}

int board_reduce_row(const Board* board, byte row, byte (*function)(const Board *, byte, byte), int initial_value)
{
    byte    index;
    int     result;

    index = 0;
    result = initial_value;
    while (index < BOARD_SIDE_SIZE)
    {
        result += function(board, row, index);
        index ++;
    }

    return result;
}

int board_reduce_col(const Board* board, byte col, byte (*function)(const Board *, byte, byte), int initial_value)
{
    byte    index;
    int     result;

    index = 0;
    result = initial_value;
    while (index < BOARD_SIDE_SIZE)
    {
        result += function(board, index, col);
        index ++;
    }

    return result;
}

static bool _row_valid(const Board* board, byte row, byte col)
{
    byte index;

    index = 0;
    while (index < BOARD_SIDE_SIZE)
    {
        if (index == col || board_at(board, row, index) == EMPTY_CELL_SYMBOL)
        {
            index ++;
            continue ;
        }

        if (board_cells_equal(board, row, col, row, index))
            return false;
        
        index ++;
    }

    return true;
}

static bool _col_valid(const Board* board, byte row, byte col)
{
    byte index;

    index = 0;
    while (index < BOARD_SIDE_SIZE)
    {
        if (index == row || board_at(board, index, col) == EMPTY_CELL_SYMBOL)
        {
            index ++;
            continue ;
        }

        if (board_cells_equal(board, row, col, index, col))
            return false;

        index ++;
    }

    return true;
}

static bool _block_valid(const Board* board, byte row, byte col)
{
    byte block_index, j, k, j_limit, k_limit;

    block_index = get_block_index(row, col);
    j = block_ul_positions[block_index][0];
    k = block_ul_positions[block_index][1];
    j_limit = j + BLOCK_SIDE_SIZE;
    k_limit = k + BLOCK_SIDE_SIZE;
    
    while (j < j_limit)
    {
        k = block_ul_positions[block_index][1];
        while (k < k_limit)
        {
            if ((j == row && k == col) || board_at(board, row, col) == EMPTY_CELL_SYMBOL)
            {
                k ++;
                continue ;
            }

            if (board_cells_equal(board, row, col, j, k))
                return false;
            
            k ++;
        }
        j ++;
    }

    return true;
}

bool board_validate(const Board* board)
{
    byte index;
    byte row;
    byte col;

    index = 0;
    while (index < BOARD_TOTAL_SIZE)
    {
        row = index_to_row(index);
        col = index_to_col(index);

        if (!_row_valid(board, row, col))
            return false;
        
        if (!_col_valid(board, row, col))
            return false;
        
        if (!_block_valid(board, row, col))
            return false;
        
        index ++;
    }

    return true;
}

static byte _count_empty_cellsROW(const Board* board, byte row)
{
    return board_reduce_row(board, row, board_cell_is_nonempty, 0);
}

static byte _count_empty_cellsCOL(const Board* board, byte col)
{
    return board_reduce_col(board, col, board_cell_is_empty, 0);
}

static byte _get_pivot_row(const Board* board)
{
    byte min_index;
    byte min_count;
    byte current_index;
    byte current_count;

    current_index = 1;
    min_count = _count_empty_cellsROW(board, 0);
    min_index = 0;

    while (current_index < BOARD_SIDE_SIZE)
    {
        current_count = _count_empty_cellsROW(board, current_index);
        if (current_count < min_count)
        {
            min_count = current_count;
            min_index = current_index;
        }
        
        current_index ++;
    }

    return min_index;
}

static byte _get_pivot_col(const Board* board, byte pivot_row)
{
    byte index;
    byte count;
    byte min_count;
    byte min_index;

    index = 0;
    min_index = 0;
    min_count = BOARD_TOTAL_SIZE;

    while (index < BOARD_SIDE_SIZE)
    {
        if (board_at(board, pivot_row, index) != EMPTY_CELL_SYMBOL)
        {
            index ++;
            continue ;
        }

        count = _count_empty_cellsCOL(board, index);
        if (count < min_count)
        {
            min_count = count;
            min_index = index;
        }

        index ++;
    }
    
    return min_index;
}

byte board_get_pivot_index(const Board* board)
{
    byte row;
    byte col;

    row = _get_pivot_row(board);
    col = _get_pivot_col(board, row);

    return row_col_to_index(row, col);
}
