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
 * Removes a value from every Cell's 'candidates' bitset in row x and column y
 */
void remove_candidate_row_col(array< array<Cell, 9>, 9>&board, int x, int y, int candidate) {
  for (int i = 0; i < 9; i++) {
    board[x][i].candidates.set((candidate - 1), 0);
    board[i][y].candidates.set((candidate - 1), 0);
  }
} /* remove_candidate_row_col() */

/*
 * Adds a value to the sector's bitset, where the sector is determined by the
 * coordinates passed in.
 */
void add_value_sector(int x, int y, int value) {
  sectors[get_sector(x, y)].set((value - 1), 1);
} /* remove_candidate_sector() */

/*
 * Removes a value 'candidate' from every cell in a sector, where the sector
 * is determined by the coordinates passed in.
 */
void remove_candidate_sector(array< array<Cell, 9>, 9>&board, int x, int y, int candidate) {
  //TODO: probably a more efficient way to do this
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (get_sector(x, y) == get_sector(i, j)) {
        board[i][j].candidates.set((candidate - 1), 0);
      }
    }
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
  add_value_sector(x, y, board[x][y].val);
  remove_candidate_sector(board, x, y, board[x][y].val);
} /* solve_cell() */

