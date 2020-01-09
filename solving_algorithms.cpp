#include <iostream>
#include <stdlib.h>
#include <cmath>

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
    cout << "single candidate:" << endl;
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
    if (y != i) {
      unique_tester |= board[x][i].candidates;
    }
  }

  unique_tester ^= board[x][y].candidates;
  unique_tester &= board[x][y].candidates;

  if (unique_tester.count() == 1) {
    // set Cell's candidates to new bitset if there is a unique value in its row
    board[x][y].candidates = unique_tester;
    cout << "unique in row:" << endl;
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
    if (x != i) {
      unique_tester |= board[i][y].candidates;
    }
  }

  unique_tester ^= board[x][y].candidates;
  unique_tester &= board[x][y].candidates;

  if (unique_tester.count() == 1) {
    // set Cell's candidates to new bitset if there is a unique value in its col
    board[x][y].candidates = unique_tester;
    cout << "unique in col:" << endl;
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
  array<array<int, 2>, 9> coords = get_sector_coords(get_sector(x, y));
  bitset<9> unique_tester =  { 0 };
  int a = 0;
  int b = 0;

  for (int i = 0; i < 9; i++) {
    a = coords[i][0];
    b = coords[i][1];
    if ((a != x) || (b != y)) {
      // OR each Cell's candidates field to get all present candidates in sector
      unique_tester |= board[a][b].candidates;
    }
  }

  unique_tester ^= board[x][y].candidates;
  unique_tester &= board[x][y].candidates;

  if (unique_tester.count() == 1) {
    // set Cell's candidates to new bitset if there is a unique value in its col
    board[x][y].candidates = unique_tester;
    cout << "unique in sector:" << endl;
    solve_cell(board, x, y);

    return true;
  }

  return false;
} /* unique_in_sector() */

/*
 * If 2 Cells in the same row/col only have 2 options (the same 2 options),
 * AND are in the same sector, those 2 Cells are the place where those options
 * must lie.
 */
bool unique_pair_in_sector(array< array<Cell, 9>, 9>&board, int x, int y) {
  if (board[x][y].narrowed_down) {
    return false;
  }

  array<array<int, 2>, 9> coords = get_sector_coords(get_sector(x, y));
  int a = 0;
  int b = 0;

  for (int i = 0; i < 9; i++) {
    a = coords[i][0];
    b = coords[i][1];


    if ((a != x) || (b != y)) {
      if ((board[a][b].candidates == board[x][y].candidates) &&
          (board[a][b].candidates.count() == 2)) {
        bitset<9> temp_candidates = board[x][y].candidates;
        // extract candidates from bitset
        int candidate[2] = {0, 0};
        int index = 0;
        for (int j =  8; j >= 0; j--) {
          if (board[a][b].candidates[j] == 1) {
            candidate[index] = j + 1;
            index++;
          }
        }

        if (a == x) {
          // Cells are in the same row, so remove those 2 candidates from the row
          remove_candidate_row(board, x, y, candidate[0]);
          remove_candidate_row(board, x, y, candidate[1]);
        }
        else if (b == y) {
          // Cells are in the same column, so remove those 2 candidates from the col
          remove_candidate_col(board, x, y, candidate[0]);
          remove_candidate_col(board, x, y, candidate[1]);
        }

        remove_candidate_sector(board, x, y, candidate[0]);
        remove_candidate_sector(board, x, y, candidate[1]);

        // adds those candidates back to the 2 Cells since we didn't solve anything
        board[x][y].candidates = temp_candidates;
        board[a][b].candidates = temp_candidates;

        // This field is to prevent an infinite loop from re-calling this
        // function on a pair of Cells that have 2 candidates (since no Cell is solved)
        board[x][y].narrowed_down = true;
        board[a][b].narrowed_down = true;

        cout << "unique pair in sector:" << endl;
        cout << "(" << a << ", " << b << ") AND (" << x << ", " << y <<
             ")  have unique candidates " << candidate[0] << " and " <<
             candidate[1] << endl;
        cout << "-----------------------------------------------------" << endl;
        return true;
      }
    }
  }
  return false;
} /* unique_pair_in_sector() */

/*
 * This function exists to minimize repeated code in the common_val_in_sector
 * function.
 */
void common_val_in_sector_helper(array< array<Cell, 9>, 9>&board,
                                 vector< vector< array<int, 2> > > combinations,
                                 array< array<int, 2>, 9> coords) {
  bitset<9> common_tester_vals = { 0 };
  common_tester_vals.set();
  bitset<9> other_cell_vals = { 0 };

  // used to temporarily store coordinates for each Cell
  int a = 0;
  int b = 0;

  // find common values between Cells that you're comparing
  for (int i = 0; i < combinations.size(); i++) {
    common_tester_vals.set();
    other_cell_vals.reset();

    for (int j = 0; j < combinations[i].size(); j++) {
      a = combinations[i][j][0];
      b = combinations[i][j][1];
      common_tester_vals &= board[a][b].candidates;
    }

    // find all present values in sector (not including Cells you're comparing)
    // using bitwise OR operation
    int valid_cell = true;
    for (int j = 0; j < coords.size(); j++) {
      valid_cell = true;
      a = coords[j][0];
      b = coords[j][1];
      for (int k = 0; k < combinations[i].size(); k++) {
        valid_cell &= ((combinations[i][k][0] != a) || (combinations[i][k][1] != b));
      }
      if (valid_cell) {
        other_cell_vals |= board[a][b].candidates;
      }
    }

    // XOR, then AND, with common values in Cells you're comparing to see if
    // there are any unique values in the Cells you're comparing
    other_cell_vals ^= common_tester_vals;
    other_cell_vals &= common_tester_vals;
    
    //TODO: might have to be a unique bit set, but I don't think I see any problem with
    //      having multiple unique bits right now
    if (other_cell_vals.count() == 1) {
      int candidate = log2(other_cell_vals.to_ulong()) + 1;
      //for (int i = 0; i < combinations.size(); i++) {
      bool same_row = true;
      bool same_col = true;

      for (int j = 0; j < combinations[i].size() - 1; j++) {
        same_row &= combinations[i][j][0] == combinations[i][j + 1][0];
        same_col &= combinations[i][j][1] == combinations[i][j + 1][1];
      }

      if (same_row) {
        // if all tester Cells are in the same row, remove_row
        cout << "common val in row --> candidate = " << candidate << endl;
        cout << "-----------------------------------------------------" << endl;

        remove_candidate_row(board, combinations[i][0][0],
                             combinations[i][0][1], candidate);
        // pt2
        remove_candidate_sector(board, combinations[i][0][0],
                                combinations[i][0][1], candidate);

        // add candidates back 
        for (int j = 0; j < combinations[i].size(); j++) {
          a = combinations[i][j][0];
          b = combinations[i][j][1];
          board[a][b].candidates.set(candidate - 1);
        }
      }
      if (same_col) {
        // if all tester Cells are in the same col, remove_col
        cout << "common val in col --> candidate = " << candidate << endl;
        cout << "-----------------------------------------------------" << endl;

        remove_candidate_col(board, combinations[i][0][0],
                             combinations[i][0][1], candidate);
        // pt2
        remove_candidate_sector(board, combinations[i][0][0],
                                combinations[i][0][1], candidate);
        // add candidates back
        for (int j = 0; j < combinations[i].size(); j++) {
          a = combinations[i][j][0];
          b = combinations[i][j][1];
          board[a][b].candidates.set(candidate - 1);
        }
      }
    }
  }
} /* common_val_in_sector_helper() */

/*
 * pt1: if there is a pair/triplet of Cells in a sector that are in the same
 *      row/column, and there is a value that is unique to all of
 *      those Cells in the sector, that value can be removed from the
 *      corresponding row/column (bitwise AND the Cells and check
 *      the rest of the sector for existence. if there are unique values,
 *      remove them from the corresponding row/col)
 * ------------------------------------------------------------------------
 * pt2: if there is a pair/triplet of Cells in a sector that are in the same
 *      row/column, and there is a value in all of those Cells that is
 *      unique to that row/column, that value can be removed from the
 *      corresponding sector (bitwise AND the cells and check
 *      for existence in the corresponding row/col)
 *
 */
void common_val_in_sector(array< array<Cell, 9>, 9>&board, int x, int y) {
  // pt1
  array< array<int, 2>, 9> coords = get_sector_coords(get_sector(x, y));

  // find all combinations of 2 coordinates
  vector< vector< array<int, 2> > > combinations;
  vector< array<int, 2> > combination;
  combination_finder(coords, 2, 0, combinations, combination);

  common_val_in_sector_helper(board, combinations, coords);

  // find all combinations of 3 coordinates
  combination_finder(coords, 3, 0, combinations, combination);

  common_val_in_sector_helper(board, combinations, coords);

} /* common_val_in_sector() */

bool brute_force(array< array<Cell, 9>, 9>&board, int x, int y, int candidate_guess) {
  return false;
} /* brute_force() */

/*
 * Wrapper function to run all solving algorithms on the cell passed in.
 *
 * common_val_in_sector is hard to keep track of, so call it once before and
 * once after the iteration to make surue that it does something when it needs
 * to. Prevents premature termination of the program.
 */
void run_solving_algorithms(array< array<Cell, 9>, 9>&board) {
  bool changed = false;
  while (1) {
    changed = false;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j].val == -1) {

          common_val_in_sector(board, i, j);

          if (single_candidate(board, i, j) == true) {
            changed |= true;
            continue;
          }
          changed |= false;
          if (unique_in_row(board, i, j)) {
            changed |= true;
            continue;
          }
          changed |= false;
          if (unique_in_col(board, i, j)) {
            changed |= true;
            continue;
          }
          changed |= false;
          if (unique_in_sector(board, i, j)) {
            changed |= true;
            continue;
          }
          changed |= false;
          //TODO: expand to unique pair in sector/row/col
          if (unique_pair_in_sector(board, i, j)) {
            changed |= true;
            continue;
          }
          changed |= false;

          common_val_in_sector(board, i, j);
        }
      }
    }
    if (!changed) {
      if (!solved(board)) {
        // #############################
        // #     BRUTE FORCE SOLVE     #
        // #############################

        for (int i = 0; i < 9; i++) {
          for (int j = 0; j < 9; j++) {
            if (board[i][j].val == -1) {
              for (int x = 0; x < 9; x++) {
                // make copy of board
                array< array<Cell, 9>, 9> board_copy = { 0 };
                copy(board.begin(), board.end(), board_copy.begin());
                
                if (board[i][j].candidates[x] == true) {
                  if (brute_force(board_copy, i, j, x + 1) == true) {
                    // if brute_force returns true, board is solved
                    board = board_copy;
                    return;
                  }
                }
              }
              cout << endl << "Board is unsolvable :(" << endl;
              return;
            }
          }
        }
      }

      cout << "          SOLVED BOARD     " << endl;
      return;

      // print candidates
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          cout << i << ", " << j << ":    " << board[i][j].candidates.to_string() << endl;
        }
      }

    }
  }
} /* run_solving_algorithms() */

