#include <iostream>
#include <stdlib.h>

#include "solving_algorithms.h"

using namespace std;

/*
 * Checks if cell has a single candidate. If it does, solve_cell().
 *
 * Returns 'true' if a cell has been changed
 */
bool single_candidate(array< array<Cell, 9>, 9>&board, int x, int y) {
  if ((board[x][y].candidates.count() == 0) && (board[x][y].val == -1)) {
    // No candidates and space is empty - unsolvable!
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

/*  #############################
 *  #   UNIQUE VALUE CHECKERS   #
 *  #############################
 */

/*
 * These functions check the Cell's row/col/sector to find out if the Cell
 * has a candidate that is unique to its row/col/sector. For example:
 * Cell2 candidates 2, 3, 4, 7, 8, 9:  1 1 1 0 0 1 1 1 0
 * Cell3 candidates 6, 7, 9         :  1 0 1 1 0 0 0 0 0  OR
 * Cell4 candidates 2, 3, 4, 6, 7, 9:  1 0 1 1 0 1 1 1 0
 * etc...                             -------------------
 *                                     1 1 1 1 0 1 1 1 0  XOR
 * Cell candidates  1, 3, 7, 8, 9   :  1 1 1 0 0 0 1 0 1
 *                                    -------------------
 *                                     0 0 0 1 0 1 0 1 1  AND
 * Cell candidates  1, 3, 7, 8, 9   :  1 1 1 0 0 0 1 0 1
 *                                    -------------------
 *                                     0 0 0 0 0 0 0 0 1
 * So the Cell has a unique candidate of 1 in its row/col/sector, therefore
 * its value must be 1.
 */

/*
 * Checks if cell has a unique candidate for the row that it's in. If it does,
 * solve_cell().
 *
 * Returns 'true' if a cell has been changed.
 */
bool unique_in_row(array< array<Cell, 9>, 9>&board, int x, int y) {
  bitset<9> unique_tester =  { 0 };

  for (int i = 0; i < 9; i++) {
    // OR each Cell's candidates field to get all present candidates in row
    unique_tester |= board[x][i].candidates;
  }

  unique_tester ^= board[x][y].candidates;
  unique_tester &= board[x][y].candidates;

  if (unique_tester.count() == 1) {
    // set Cell's candidates to new bitset if there is a unique value in its row
    board[x][y].candidates = unique_tester;
    solve_cell(board, x, y);
    return true;
  }

  return false;
} /* unique_in_row() */

/*
 * Checks if cell has a unique candidate for the col that it's in. If it does,
 * solve_cell().
 *
 * Returns 'true' if a cell has been changed.
 */
bool unique_in_col(array< array<Cell, 9>, 9>&board, int x, int y) {
  bitset<9> unique_tester =  { 0 };

  for (int i = 0; i < 9; i++) {
    // OR each Cell's candidates field to get all present candidates in col
    unique_tester |= board[i][y].candidates;
  }

  unique_tester ^= board[x][y].candidates;
  unique_tester &= board[x][y].candidates;

  if (unique_tester.count() == 1) {
    // set Cell's candidates to new bitset if there is a unique value in its col
    board[x][y].candidates = unique_tester;
    solve_cell(board, x, y);
    return true;
  }

  return false;
} /* unique_in_col() */
/*
 * Checks if cell has a unique candidate for the sector that it's in. If it
 * does, solve_cell().
 *
 * Returns 'true' if a cell has been changed.
 */

bool unique_in_sector(array< array<Cell, 9>, 9>&board, int x, int y) {
  bitset<9> unique_tester =  { 0 };

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      // OR each Cell's candidates field to get all present candidates in sector
      if (get_sector(x, y) == get_sector(i, j)) {
        unique_tester |= board[i][j].candidates;
      }
    }
  }

  unique_tester ^= board[x][y].candidates;
  unique_tester &= board[x][y].candidates;

  if (unique_tester.count() == 1) {
    // set Cell's candidates to new bitset if there is a unique value in its col
    board[x][y].candidates = unique_tester;
    solve_cell(board, x, y);
    return true;
  }

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
        if (board[i][j].val == -1) {
          changed |= single_candidate(board, i, j);
          changed |= unique_in_row(board, i, j);
          changed |= unique_in_col(board, i, j);
          changed |= unique_in_sector(board, i, j);
        }
      }
    }
    if (!changed) {
      return;
    }
  }
} /* run_solving_algorithmsm() */

