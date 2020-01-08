# Sudoku Solver in C++
## Created by Chris Cohen on 12/17/19

### Solving Algorithms
- SINGLE CANDIDATE
  - If a Cell has a single candidate, solve for that Cell with that candidate
- UNIQUE IN ROW/COL/SECTOR
  - If a Cell has a unique value in its row/col/sector, solve for that Cell with the unique value
- UNIQUE PAIR IN SECTOR
  - If there are 2 Cells with a matching pair of possibilities, those two Cells must contain those values
  - If the Cells are in the same row/col, both of the values in that pair can be eliminated from that row/col

### TODO
- Logging
- Brute Force
