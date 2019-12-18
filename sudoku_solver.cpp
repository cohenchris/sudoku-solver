#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdlib.h>
using namespace std;

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

int main(int argc, char * argv[]) {
  char game_board[9][9] = { 0 };
  switch(argc) {
    case 2:
      read_board(game_board, argv[1]);
      break;
    default:
      cout << "Usage: ./sudoku_solver <filename>" << endl << endl;
      cout << "Board must be 9x9 with blank spaces represented by a '.'" << endl;
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << game_board[i][j];
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
} /* main() */
