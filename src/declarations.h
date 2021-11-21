#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "definitions.h"
#include "why_lib.h"

Board*      board_create(const char* values);
void        board_destroy(Board* board);
Board*      board_copy(const Board* board);
byte        index_to_row(byte index);
byte        index_to_col(byte index);
byte        row_col_to_index(byte row, byte col);
void        board_set_at_index(Board* board, byte value, byte index);
void        board_set(Board* board, byte value, byte row, byte col);
byte        board_at_index(const Board* board, byte index);
byte        board_at(const Board* board, byte row, byte col);
byte        board_atS(const Board* board, byte col, byte row);
bool        board_cells_equal(const Board* board, byte row_a, byte col_a, byte row_b, byte col_b);
bool        board_validate(const Board* board);
byte        board_get_pivot_index(const Board* board);
bool        board_is_solved(const Board* board);
Board*      board_solve(const Board* board);

int         get_block_index(byte row, byte col);
int         get_block_indexI(byte cell_index);

int_signed  comapre_byte_pointers(const byte* lhs, const byte* rhs);
Set*        _get_digit_set();
Set*        compute_available_values(const Board* board, byte pivot_index);

void        print_board(const Board* board);
void        _print_byteP(const byte* byte);
void        print_index(byte index);
void        print_separator();


char*       input_get_values(const char* filename);

#endif
