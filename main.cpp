#include <iostream>
#include <stdio.h>
#include <array>
#include <bitset>
#include <fstream>
#include <chrono>

#include "board_parser.h"
#include "solving_algorithms.h"

using namespace std;

int main(int argc, char ** argv) {
  auto start = chrono::steady_clock::now();
  array< array<Cell, 9>, 9> game_board;

  switch(argc) {
    case 2:
      parse_board(game_board, argv[1]);
      cout << "         ORIGINAL BOARD    " << endl;
      print_board(game_board);
      cout << "-----------------------------------------------------" << endl;
      run_solving_algorithms(game_board);
      break;
    default:
      cout << "Usage: sudoku_solver <filename>" << endl << endl;
      cout << "Board must have dimensions 9x9 with blank spaces "
              "represented by a '.'" << endl;
      exit(EXIT_FAILURE);
  }
  print_board(game_board);
  auto end = chrono::steady_clock::now();
  cout << endl << "Elapsed time in milliseconds: " 
       << chrono::duration_cast<chrono::milliseconds>(end - start).count()
       << " ms" << endl;

  //print_cell_data(game_board);

  exit(EXIT_SUCCESS);
} /* main() */
