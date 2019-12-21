#include <iostream>
#include <cmath>
#include <stdlib.h>

#include "solving_algorithms.h"

using namespace std;

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
  remove_candidate_sector(x, y, board[x][y].val);
} /* solve_cell() */

/*
 * Checks if cell has a single candidate. If it does, solve_cell().
 *
 * Returns 'true' if a cell has been changed
 */
bool single_candidate(array< array<Cell, 9>, 9>&board, int x, int y) {
  if ((board[x][y].candidates.count() == 0) && (board[x][y].val == -1)) {
    // No candidates and space is empty - unsolvable!
    cout << x << ", " << y << endl;
    cout << "candidates: " << board[x][y].candidates.to_string() << endl;
    cout << endl << "Board is unsolvable :(" << endl;
    print_board(board);
    exit(EXIT_FAILURE);
  }
  else if (board[x][y].candidates.count() == 1) {
    // if only 1 bit is set, cell is solvable!
    solve_cell(board, x, y);
    return true;
  }

  return false;
} /* single_candidate() */

bool unique_in_row(array< array<Cell, 9>, 9>&board, int x, int y) {
  return false;
} /* unique_in_row() */

bool unique_in_col(array< array<Cell, 9>, 9>&board, int x, int y) {
  return false;
} /* unique_in_col() */

bool unique_in_sector(array< array<Cell, 9>, 9>&board, int x, int y) {
  return false;
} /* unique_in_sector() */

/*
 * Wrapper function to run all solving algorithms on the cell passed in.
 */
void run_solving_algorithms(array< array<Cell, 9>, 9>&board) {
  bool changed = false;
  while (1) {
    changed = false;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        changed |= single_candidate(board, i, j);
        changed |= unique_in_row(board, i, j);
        changed |= unique_in_col(board, i, j);
        changed |= unique_in_sector(board, i, j);

      }
    }
    if (!changed) {
      return;
    }
  }
} /* run_solving_algorithmsm() */

