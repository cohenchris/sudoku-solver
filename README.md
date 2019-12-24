# Sudoku Solver in C++
## Created by Chris Cohen on 12/17/19

### Solving Algorithms
- If a Cell has a single candidate, solve for that Cell with that candidate
- If a Cell has a unique value in its row/col/sector, solve for that Cell with the unique value

### Algorithms TODO
- If 2 Cells in the same row/col only have 2 options (the same 2 options), AND are in the same sector, those 2 Cells are the place where those options must lie
