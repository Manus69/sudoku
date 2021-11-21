#include "declarations.h"
#include "board.h"

// #include "why_tree_diagnostics.h"

#define CHECK_TREE 0
#define DBG_PRINT 0

static Board* _solve(const Board* board);

static Board* _try(const Board* board, byte pivot, byte value)
{
    Board* next_board;
    Board* solved_board;

    next_board = board_copy(board);
    board_set_at_index(next_board, value, pivot);

    if (board_is_solved(next_board))
        return next_board;
    
    solved_board = _solve(next_board);
    board_destroy(next_board);

    return solved_board;
}

static Board* _solve(const Board* board)
{
    byte    pivot;
    Set*    available_values;
    byte    value;
    Board*  next_board;

    pivot = board_get_pivot_index(board);
    available_values = compute_available_values(board, pivot);
    next_board = NULL;

    while (set_get_size(available_values))
    {
        value = *(byte *)set_pop_min(available_values);
        next_board = _try(board, pivot, value);

        if (next_board)
            break ;
    }

    set_destroy(available_values);

    return next_board;
}

Board* board_solve(const Board* board)
{
    if (!board_validate(board))
        return NULL;
    
    if (board->empty_cell_count == 0)
        return board_copy(board);
    
    return _solve(board);
}