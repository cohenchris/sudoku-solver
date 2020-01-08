#ifndef CELL_FUNCTIONS_H
#define CELL_FUNCTIONS_H

#include <array>
#include <vector>

#include "Cell.cpp"

using namespace std;

/*
 * Bitsets are in this form:
 * values:    9 8 7 6 5 4 3 2 1
 * bitset:    0 0 0 0 0 0 0 0 0 
 *
 * A bit in the bitset that is 1 represents that a number is
 * present in the row/col/sector.
 */

extern array<bitset<9>, 9> rows;
extern array<bitset<9>, 9> cols;
extern array<bitset<9>, 9> sectors;

int get_sector(int x, int y);
array<array<int, 2>, 9> get_sector_coords(int sector);
void solve_cell(array< array<Cell, 9>, 9>&board, int x, int y);
void remove_candidate_row_col(array< array<Cell, 9>, 9>&board, int x, int y, int candidate);
void remove_candidate_row(array< array<Cell, 9>, 9>&board, int x, int y, int candidate);
void remove_candidate_col(array< array<Cell, 9>, 9>&board, int x, int y, int candidate);
void remove_candidate_sector(array< array<Cell, 9>, 9>&board, int x, int y, int candidate);
void add_value_sector(int x, int y, int value);
void combination_finder(array< array<int, 2>, 9> coords, int n, int offset,
                        vector< vector< array<int, 2> > > &combinations,
                        vector< array<int, 2> > &combination);

#endif
