#include <string>
#include <array>

#include "Cell.cpp"

using namespace std;
class Cell;

// main function that does everything you need
void parse_board(array< array<Cell, 9>, 9>&board, string const file_name);
void print_board(array< array<Cell, 9>, 9>&board);
void print_cell_data(array< array<Cell, 9>, 9>&board);

void read_board(array< array<Cell, 9>, 9>&board, string const file_name);
static void initialize_bitsets(array< array<Cell, 9>, 9>&board);
int get_sector(int x, int y);
void remove_candidate_row_col(array< array<Cell, 9>, 9>&board, int x, int y, int candidate);
void remove_candidate_sector(int x, int y, int candidate);

