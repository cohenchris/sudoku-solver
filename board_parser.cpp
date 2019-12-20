#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdlib.h>
using namespace std;

/*
 * Nicely prints the board so you can see all sectors divided up.
 */
void print_board(array< array<Cell, 9>, 9>&board) {
  cout << "------------------------------" << endl;
  for (int i = 0; i < 9; i++) {
    if (i == 2 || i == 5 || i == 8) {
      cout << "------------------------------" << endl;
    }
    for (int j = 0; j < 9; j++) {
      if (j == 0 || j == 3 || j == 6) {
        cout << "|";
      }
      if (board[i][j] == -1) {
        cout << " . ";
      }
      else {
        cout << board[i][j];
      }
    }
    cout << "|" << endl;
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

void read_board(char (&board)[9][9], string const file_name) {
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

  while ((!board_file.eof()) && (line_num < 9)) {
    getline(board_file, line, '\n');

    if (line.size() > 9) {
      cout << "Board must be 9x9 with blank spaces represented by a '.'" << endl;
      exit(EXIT_FAILURE);
    }
    if (line_num > 9) {
      cout << "Board must be 9x9 with blank spaces represented by a '.'" << endl;
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 9; i++) {
      sudoku_char.assign(1, line[i]);
      if (!regex_match(sudoku_char, valid_sudoku_char)) {
        cout << "Board must be 9x9 with blank spaces represented by a '.'" << endl;
        exit(EXIT_FAILURE);
      }
      board[line_num][i] = line[i];
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
static void initialize_sectors(array< array<Cell, 9>, 9>&board) {

} /* initialize_sectors() */

int get_sector() {

} /* get_sector() */

void remove_candidate_row_col(array< array<Cell, 9>, 9>&board, int x, int y, int candidate) {

} /* remove_candidate_row_col() */

void remove_candidate_sector(int x, int y, int candidate) {

} /* remove_candidate_sector() */

/*
 * ##############################
 * #    MAIN WRAPPER FUNCTION   #
 * ##############################
 */
void parse_board(array< array<Cell, 9>, 9>&board, string const file_name) {
  read_board(board);
  initialize_sectors(board);
} /* parse_board() */
