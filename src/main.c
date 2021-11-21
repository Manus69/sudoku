#include "declarations.h"

#include <stdio.h>

#define HELP_FLAG "--help"

void _at_exit()
{
    get_line(-1);
}

int display_usage()
{
    printf("Usage: ./sudoku [filename] to read from file or ./sudoku to read from sudoku.txt\n");

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    char*   values;
    Board*  board;
    Board*  solved_board;
    clock_t start;
    clock_t end;

    start = clock();
    atexit(_at_exit);
    values = NULL;

    if (argc == 1)
        values = input_get_values("sudoku.txt");
    else if (argc == 2 && cstr_compare(argv[1], HELP_FLAG) == 0)
        return display_usage();
    else if (argc == 2)
        values = input_get_values(argv[1]);
    else
        return display_usage();

    if (!values)
        return (long)error_display_return();

    board = board_create(values);
    print_board(board);
    solved_board = board_solve(board);
    print_board(solved_board);

    free(values);
    board_destroy(board);
    board_destroy(solved_board);
    end = clock();
    print_time_diff(start, end);

    return EXIT_SUCCESS;
}