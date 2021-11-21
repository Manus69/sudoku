#include "board.h"
#include "definitions.h"
#include "declarations.h"

#define DBG 0
#define CHECK_SIZE 0

extern int block_ul_positions[BOARD_SIDE_SIZE][2];

int_signed comapre_byte_pointers(const byte* lhs, const byte* rhs)
{
    return *rhs - *lhs;
}

Set* _get_digit_set()
{
    Set*    digits;
    byte*   digit; 

    digits = set_create(copy_shallow, destroy_shallow, comapre_byte_pointers);
    digit = (byte *)DIGITS;
    while (*digit)
    {
        set_insert(digits, digit);
        digit ++;
    }

    return digits;
}

static void _cast_out_row_col_elements(const Board* board, Set* set, byte index, byte (*at)(const Board* , byte, byte))
{
    byte _index;
    byte value;

    _index = 0;
    while (_index < BOARD_SIDE_SIZE)
    {
        value = at(board, index, _index);
        if (value != EMPTY_CELL_SYMBOL)
            set_remove(set, &value);
        
        #if CHECK_SIZE
            tree_check_size(set);
        #endif

        _index ++;
    }
}

static void _cast_out_block_elements(const Board* board, Set* set, byte index)
{
    byte block_index, j, k, j_limit, k_limit, value;

    block_index = get_block_indexI(index);
    j = block_ul_positions[block_index][0];
    k = block_ul_positions[block_index][1];
    j_limit = j + BLOCK_SIDE_SIZE;
    k_limit = k + BLOCK_SIDE_SIZE;

    while (j < j_limit)
    {
        k = block_ul_positions[block_index][1];
        while (k < k_limit)
        {
            value = board_at(board, j, k);
            if (value != EMPTY_CELL_SYMBOL)
                set_remove(set, &value);

            k ++;
        }
        j ++;
    }
}

Set* compute_available_values(const Board* board, byte pivot_index)
{
    Set* available_values;

    available_values = _get_digit_set();
    _cast_out_row_col_elements(board, available_values, index_to_row(pivot_index), board_at);
    _cast_out_row_col_elements(board, available_values, index_to_col(pivot_index), board_atS);
    _cast_out_block_elements(board, available_values, pivot_index);

    return available_values;
}