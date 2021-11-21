#include "definitions.h"
#include "why_lib.h"

static void _error_set()
{
    error_set(WHY_ERROR_PARSE, NULL);
}

static void _process_line(char* values, Array* line_array)
{
    int     index;
    char*   string_content;

    if (array_size(line_array) != BOARD_SIDE_SIZE)
        return _error_set();

    index = 0;
    while (index < array_size(line_array))
    {
        string_content = string_get_characters(array_at(line_array, index));

        if (cstr_length(string_content) != 1)
            return _error_set();

        if (!id_digit(string_content) && *string_content != EMPTY_CELL_SYMBOL)
            return _error_set();

        *values = *string_content;
        values ++;
        index ++;
    }
}

static char* _process_lines(const Array* lines)
{
    char*   values;
    String* line;
    Array*  line_array;
    int     index;

    values = memory_zero(BOARD_TOTAL_SIZE + 1);
    index = 0;

    while (index < array_size(lines))
    {
        line = array_at(lines, index);
        line_array = string_split(line, ' ');

        _process_line(values, line_array);

        values += BOARD_SIDE_SIZE;
        array_destroy(line_array);
        index ++;

        if (WHY_ERROR)
        {
            free(values - index * BOARD_SIDE_SIZE);
            return NULL;
        }
    }

    return values - BOARD_TOTAL_SIZE;
}

char* input_get_values(const char* filename)
{
    Array*  lines;
    char*   values;

    lines = get_all_linesAFN(filename);

    if (!lines)
        return error_set(WHY_ERROR_FILE, "Could not open the file\n");

    if (array_size(lines) != BOARD_SIDE_SIZE)
    {
        _error_set();
        array_destroy(lines);

        return NULL;
    }

    values = _process_lines(lines);
    array_destroy(lines);

    return values;
}