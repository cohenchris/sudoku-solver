#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <array>
#include <bitset>

#include "board_parser.h"

using namespace std;

/*
 * Sector bitset is in this form:
 * sectors:   9 8 7 6 5 4 3 2 1
 * bitset:    0 0 0 0 0 0 0 0 0 
 *
 * A bit in the bitset that is 1 represents that a number is
 * present in the sector.
 */
array< bitset<9>, 9 > sectors = { 0 };

/*
 * Nicely prints the board so you can see all sectors divided up.
 */
void print_board(array< array<Cell, 9>, 9>&board) {
  cout << "-------------------------------" << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (j == 0 || j == 3 || j == 6) {
        cout << "|";
      }
      if (board[i][j].val == -1) {
        cout << " . ";
      }
      else {
        cout << " " << board[i][j].val << " ";
      }

    }
    cout << "|" << endl;
    if (i == 2 || i == 5 || i == 8) {
      cout << "-------------------------------" << endl;
    }
  }
} /* print_board() */

/*
 * Prints the data stored for each Cell (coordinates, value, candidates).
 */
void print_cell_data(array< array<Cell, 9>, 9>&board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << "-------------" << endl;
      cout << i << ", " << j << endl;
      cout << "value:" << endl;
      cout << "   " << board[i][j].val << endl;
      cout << "candidates:" << endl;
      cout << "   123456789" << endl;
      cout << "   " << board[i][j].candidates.to_string() << endl;
      cout << "-------------" << endl << endl;
    }
  }
} /* print_cell_data() */

/*
 * Reads in the file that is passed in from main(), and stores the board into a
 * 2D array of Cells to be used later. A value of '-1' in a Cell represents an
 * empty cell, and any other positive value 1-9 represents a present value.
 */
void read_board(array< array<Cell, 9>, 9>&board, string const file_name) {
  // test if file exists
  ifstream ifile(file_name);
  if (!((bool) ifile)) {
    cout << "File '" << file_name << "' does not exist." << endl;
    exit(EXIT_FAILURE);
  }

  regex valid_sudoku_char("[0-9\\.]{1}");
  ifstream board_file;
  board_file.open(file_name.c_str());
  string line = "";
  int line_num = 0;
  string sudoku_char = "";

  /* 
   * Loops through each line, parsing every character, until the end of the
   * file is reached. If, at any point, the program detects invalid input or
   * formatting, it will terminate.
   */

  while ((!board_file.eof()) && (line_num < 9)) {
    getline(board_file, line, '\n');

    if (line.size() > 9 || line_num > 9) {
      cout << "Board must be 9x9 with blank spaces represented by a '.'" << endl;
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 9; i++) {
      sudoku_char.assign(1, line[i]);
      if (!regex_match(sudoku_char, valid_sudoku_char)) {
        cout << "Board must be 9x9 with blank spaces represented by a '.'" << endl;
        exit(EXIT_FAILURE);
      }
      if (line[i] == '.') {
        board[line_num][i] = Cell(-1);
      }
      else {
        // subtracting '0' translates the ascii value of the read in number into the real value
        board[line_num][i] = Cell(line[i] - '0');
      }
    }
    line_num++;
  }

  board_file.close();
} /* read_board */

/*
 * ##########################
 * #    SECTOR FUNCTIONS    #
 * ##########################
 */

/*
 * Initializes each sector's bitset based on the values that are initially
 * present in the board.
 */
static void initialize_sectors(array< array<Cell, 9>, 9>&board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      /* 
       * If (board[i][j].val - 1) is N, this sets the Nth bit in the
       * sector's bits to 1 for later use.
       */
      if (board[i][j].val != -1) {
        cout << "found a " << board[i][j].val << " in sector " << get_sector(i, j) << endl;
        sectors[get_sector(i, j)].set(board[i][j].val - 1, 1);
      }
    }
  }
} /* initialize_sectors() */

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
 * Removes a value from a sector's bitset, where the sector is determined by
 * the coordinates passed in.
 */
void remove_candidate_sector(int x, int y, int candidate) {
  sectors[get_sector(x, y)].set((candidate - 1), 0);
} /* remove_candidate_sector() */

/*
 * ##############################
 * #    MAIN WRAPPER FUNCTION   #
 * ##############################
 */

void parse_board(array< array<Cell, 9>, 9>&board, string const file_name) {
  read_board(board, file_name);
  initialize_sectors(board);
  initialize_cell_candidates(board);
} /* parse_board() */

