#include <iostream>
#include <string>
#include <bitset>
#include <array>
#include <cmath>

#include "cell_functions.h"

using namespace std;

/*
 * Gets sector number based on coordinates. Sector layout is below:
 *
 * -------------
 * | 0 | 1 | 2 |
 * -------------
 * | 3 | 4 | 5 |
 * -------------
 * | 6 | 7 | 8 |
 * -------------
 *
 *  Each sector is 3x3, where coordinate (0, 0) is in the top left
 */
int get_sector(int x, int y) {
  if (x >= 0 && x <= 2) {
    if (y >= 0 && y <= 2)       { return 0; }
    else if (y >= 3 && y <= 5)  { return 1; }
    else if (y >= 6 && y <= 8)  { return 2; }
  }
  else if (x >= 3 && x <= 5) {
    if (y >= 0 && y <= 2)       { return 3; }
    else if (y >= 3 && y <= 5)  { return 4; }
    else if (y >= 6 && y <= 8)  { return 5; }
  }
  else if (x >= 6 && x <= 8) {
    if (y >= 0 && y <= 2)       { return 6; }
    else if (y >= 3 && y <= 5)  { return 7; }
    else if (y >= 6 && y <= 8)  { return 8; }
  }
} /* get_sector() */

/*
 * Returns an array of coordinates for the requested sector.
 */
array<array<int, 2>, 9> get_sector_coords(int sector) {
  switch(sector) {
    case 0:
      return {{{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}}};
      break;
    case 1:
      return {{{0, 3}, {0, 4}, {0, 5}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5}}};
      break;
    case 2:
      return {{{0, 6}, {0, 7}, {0, 8}, {1, 6}, {1, 7}, {1, 8}, {2, 6}, {2, 7}, {2, 8}}};
      break;
    case 3:
      return {{{3, 0}, {3, 1}, {3, 2}, {4, 0}, {4, 1}, {4, 2}, {5, 0}, {5, 1}, {5, 2}}};
      break;
    case 4:
      return {{{3, 3}, {3, 4}, {3, 5}, {4, 3}, {4, 4}, {4, 5}, {5, 3}, {5, 4}, {5, 5}}};
      break;
    case 5:
      return {{{3, 6}, {3, 7}, {3, 8}, {4, 6}, {4, 7}, {4, 8}, {5, 6}, {5, 7}, {5, 8}}};
      break;
    case 6:
      return {{{6, 0}, {6, 1}, {6, 2}, {7, 0}, {7, 1}, {7, 2}, {8, 0}, {8, 1}, {8, 2}}};
      break;
    case 7:
      return {{{6, 3}, {6, 4}, {6, 5}, {7, 3}, {7, 4}, {7, 5}, {8, 3}, {8, 4}, {8, 5}}};
      break;
    case 8:
      return {{{6, 6}, {6, 7}, {6, 8}, {7, 6}, {7, 7}, {7, 8}, {8, 6}, {8, 7}, {8, 8}}};
      break;
    default:
      cout << "Error! Sector coordinates must be between 0-8, inclusive." << endl;
      exit(EXIT_FAILURE);
  }
} /* get_sector_coords() */

/*
 * Removes a value from every Cell's 'candidates' bitset in row x and column y.
 * No error checking - DANGEROUS!
 */
void remove_candidate_row_col(array< array<Cell, 9>, 9>&board, int x, int y, int candidate) {
  for (int i = 0; i < 9; i++) {
    board[x][i].candidates.set((candidate - 1), 0);
    board[i][y].candidates.set((candidate - 1), 0);
  }
} /* remove_candidate_row_col() */

/*
 * Removes a value from every Cell's 'candidates' bitset in row x
 */
void remove_candidate_row(array< array<Cell, 9>, 9> &board, int x, int y, int candidate) {
  for (int i = 0; i < 9; i++) {
    //if (i != y) {
      board[x][i].candidates.set((candidate - 1), 0);
    //}
  }
} /* remove_candidate_row() */

/*
 * Removes a value from every Cell's 'candidates' bitset in column y
 */
void remove_candidate_col(array< array<Cell, 9>, 9> &board, int x, int y, int candidate) {
  for (int i = 0; i < 9; i++) {
    //if (i != x) {
    board[i][y].candidates.set((candidate - 1), 0);
    //}
  }
} /* remove_candidate_col() */

/*
 * Adds a value to the sector's bitset, where the sector is determined by the
 * coordinates passed in.
 */
void add_value_sector(int x, int y, int value) {
  sectors[get_sector(x, y)].set((value - 1), 1);
} /* add_value_sector() */

/*
 * Removes a value 'candidate' from every cell in a sector, where the sector
 * is determined by the coordinates passed in.
 */
void remove_candidate_sector(array< array<Cell, 9>, 9>&board, int x, int y, int candidate) {
  array<array<int, 2>, 9> coords = get_sector_coords(get_sector(x, y));
  int a = 0;
  int b = 0;
  for (int i = 0; i < 9; i++) {
    a = coords[i][0];
    b = coords[i][1];
    //if ((a != x) && (b != y)) {
    board[a][b].candidates.set((candidate - 1), 0);
    //}
  }
} /* remove_candidate_sector() */
/*
 * Given a cell, performs (log2(candidates) + 1), translating the single set
 * candidate bit into the solved number. Also resets candidate bits for easier
 * use later. Makes sure that the solved value is removed from candidacy from
 * the Cell's row, column, and sector.
 * 
 */
void solve_cell(array< array<Cell, 9>, 9>&board, int x, int y) {
  // extract value from bitset
  board[x][y].val = log2(board[x][y].candidates.to_ulong()) + 1;
  // reset bits to 0 to avoid confusion later
  board[x][y].candidates.reset();

  remove_candidate_row_col(board, x, y, board[x][y].val);
  remove_candidate_sector(board, x, y, board[x][y].val);
  add_value_sector(x, y, board[x][y].val);
} /* solve_cell() */

