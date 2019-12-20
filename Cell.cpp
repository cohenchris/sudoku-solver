#include <bitset>

using namespace std;

class Cell {
  public:
    int val;
    bitset<9> candidates = 0;

    Cell(int new_val) {
      val = new_val;
    }
    Cell() {
      val = -1;
    }
};

