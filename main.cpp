#include <iostream>
#include <stdio.h>
#include <array>
#include <bitset>

#include "board_parser.h"

using namespace std;

int main(int argc, char ** argv) {
  array< array<Cell, 9>, 9> game_board;

  switch(argc) {
    case 2:
      parse_board(game_board, argv[1]);
      break;
    default:
      cout << "Usage: sudoku_solver <filename>" << endl << endl;
      cout << "Board must have dimensions 9x9 with blank spaces "
              "represented by a '.'" << endl;
      exit(EXIT_FAILURE);
  }
  //cout << "    SOLVED BOARD     " << endl;
  print_board(game_board);

  print_cell_data(game_board);

  exit(EXIT_SUCCESS);
} /* main() */
