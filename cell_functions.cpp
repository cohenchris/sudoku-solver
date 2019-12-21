#include <iostream>
#include <string>
#include <bitset>
#include <array>

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
    cout << "removed " << candidate << " from " << x << ", " << i << endl;
    board[x][i].candidates.set((candidate - 1), 0);
    cout << "removed " << candidate << " from " << i << ", " << y << endl;
    board[i][y].candidates.set((candidate - 1), 0);
  }
} /* remove_candidate_row_col() */

/*
 * Removes a value from a sector's bitset, where the sector is determined by
 * the coordinates passed in.
 */
void remove_candidate_sector(int x, int y, int candidate) {
  cout << "removed " << candidate << " from sector " << get_sector(x, y) << endl;
  sectors[get_sector(x, y)].set((candidate - 1), 0);
} /* remove_candidate_sector() */

