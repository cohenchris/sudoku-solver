#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <array>
#include <bitset>

#include "board_parser.h"

using namespace std;

array<bitset<9>, 9> rows = { 0 };
array<bitset<9>, 9> cols = { 0 };
array<bitset<9>, 9> sectors = { 0 } ;

/*
 * Nicely prints the board so you can see all sectors divided up.
 */
void print_board(array< array<Cell, 9>, 9>&board) {
  cout << "+---------+---------+---------+" << endl;
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
      cout << "+---------+---------+---------+" << endl;
    }
  }
} /* print_board() */

/*
 * Prints the data stored for each Cell (coordinates, value, candidates).
 */
void print_cell_data(array< array<Cell, 9>, 9>&board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j].candidates.count() != 0) {
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
 * Initializes each row/col/sector's bitset based on the values that are initially
 * present in the board.
 */
static void initialize_bitsets(array< array<Cell, 9>, 9>&board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      /* 
       * If (board[i][j].val - 1) is N, this sets the Nth bit in the
       * row/col/sector's bits to 1 for later use.
       */
      if (board[i][j].val != -1) {
        sectors[get_sector(i, j)].set((board[i][j].val - 1), 1);
        rows[i].set((board[i][j].val - 1), 1);
        cols[j].set((board[i][j].val - 1), 1);
      }
    }
  }
} /* initialize_sectors() */

/*
 * Initializes the 'candidates' field in each Cell based on what is present in
 * the row/col/sector. For example:
 * Row contains 2, 3, 4, 7, 8, 9:  1 1 1 0 0 1 1 1 0
 * Col contains 1, 3, 6, 7, 9   :  1 0 1 1 0 0 1 0 1
 * Sector contains 3, 4, 6, 7, 9:  1 0 1 1 0 1 1 0 0
 *                                -------------------
 *           'OR' INPUTS TOGETHER  0 0 0 0 1 0 0 0 0
 *                                 9 8 7 6 5 4 3 2 1
 * So the only candidate for this example Cell is 5.
 */
static void initialize_cell_candidates(array< array<Cell, 9>, 9>&board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j].val == -1) {
        board[i][j].candidates = (rows[i] | cols[j] | sectors[get_sector(i, j)]).flip();
      }
    }
  }
} /* initialize_cell_candidates() */

/*
 * ##############################
 * #    MAIN WRAPPER FUNCTION   #
 * ##############################
 */

void parse_board(array< array<Cell, 9>, 9>&board, string const file_name) {
  read_board(board, file_name);
  initialize_bitsets(board);
  initialize_cell_candidates(board);
} /* parse_board() */

