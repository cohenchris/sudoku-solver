#ifndef BOARD_PARSER_H
#define BOARD_PARSER_H

#include <string>
#include <array>

#include "cell_functions.h"

using namespace std;

// main function that does everything you need
void parse_board(array< array<Cell, 9>, 9>&board, string const file_name);
void print_board(array< array<Cell, 9>, 9>&board);
void print_cell_data(array< array<Cell, 9>, 9>&board);
bool solved(array< array<Cell, 9>, 9>&board);

void read_board(array< array<Cell, 9>, 9>&board, string const file_name);
static void initialize_bitsets(array< array<Cell, 9>, 9>&board);

#endif
