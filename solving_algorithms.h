#ifndef SOLVING_ALGORITHMS_H
#define SOLVING_ALGORITHMS_H

#include <string>

#include "board_parser.h"

using namespace std;

void run_solving_algorithms(array< array<Cell, 9>, 9>&board);

bool single_candidate(array< array<Cell, 9>, 9>&board, int x, int y);
bool unique_in_row(array< array<Cell, 9>, 9>&board, int x, int y);
bool unique_in_col(array< array<Cell, 9>, 9>&board, int x, int y);
bool unique_in_sector(array< array<Cell, 9>, 9>&board, int x, int y);
void common_val_in_sector(array< array<Cell, 9>, 9>&board, int x, int y);
void common_val_in_sector_helper(array< array<Cell, 9>, 9>&board,
                                 vector< vector< array<int, 2> > > combinations,
                                 array< array< int, 2>, 9> coords);

bool brute_force(array< array<Cell, 9>, 9>&board, int x, int y, int candidate_guess);

#endif
