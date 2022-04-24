#include <cassert>
#include <cstring>

#include "global_defs.h"
#include "minefield.h"
#include "minesweeper.h"

int main(int argc, char* argv[]) {
  minefield_c* m_minefield;
  minesweeper_c* m_minesweeper;
  
  if (argc == 1) { // default: medium
    m_minefield = new minefield_c(config[1][0], config[1][1], config[1][2]);
  }
  else {
    if (!strcmp(argv[1], "easy")) {
      int n_row = config[0][0];
      int n_col = config[0][1];
      int n_mine = config[0][2];
      m_minefield = new minefield_c(n_row, n_col, n_mine);
    }
    else if (!strcmp(argv[1], "medium")) {
      int n_row = config[1][0];
      int n_col = config[1][1];
      int n_mine = config[1][2];
      m_minefield = new minefield_c(n_row, n_col, n_mine);
    }
    else if (!strcmp(argv[1], "hard")) {
      int n_row = config[2][0];
      int n_col = config[2][1];
      int n_mine = config[2][2];
      m_minefield = new minefield_c(n_row, n_col, n_mine);
    }
    else
      assert(0);
  }

  m_minesweeper = new minesweeper_c(m_minefield);

  int ret = 0;
  m_minefield->disp_minefield(0, 0);
  while (ret == 0) {
    ret = m_minesweeper->action();
  }

  delete m_minesweeper;
  delete m_minefield;

  return 0;
}
