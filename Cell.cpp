#include <bitset>

using namespace std;

class Cell {
  public:
    int val;
    bitset<9> candidates = 0;
    bool narrowed_down = false;

    Cell(int new_val) {
      val = new_val;
    }
    Cell() {
      val = -1;
    }
};

