#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "minesweeper.h"

//using namespace std;

minesweeper_c::minesweeper_c(minefield_c* m_minefield) {
  this->m_minefield = m_minefield;
  cur_row = 0;
  cur_col = 0;
}

minesweeper_c::~minesweeper_c() {
}

int minesweeper_c::action() {
  char key;
  int ret = 0;
  key = getch_(0);

  if (key == 'h')
    update_curser(WEST);
  else if (key == 'j')
    update_curser(SOUTH);
  else if (key == 'k')
    update_curser(NORTH);
  else if (key == 'l')
    update_curser(EAST);
  else if (key == 'q')
    ret = m_minefield->check_no_mine(cur_row, cur_col);
  else if (key == 'w')
    m_minefield->check_mine(cur_row, cur_col);
  else if (key == 'e')
    ret = m_minefield->check_neighbors(cur_row, cur_col);

  if (ret == -1) {
    m_minefield->bomb(cur_row, cur_col);
  }
  else if (ret == 1) {
    m_minefield->done();
  }
  else {
    m_minefield->disp_minefield(cur_row, cur_col);
  }
  // debugging
  //m_minefield->disp_hiddenfield();

  return ret;
}

void minesweeper_c::update_curser(int dir) {
  switch (dir) {
  case WEST:
    if (cur_col > 0)
      cur_col--;
    break;
  case EAST:
    if (cur_col < m_minefield->n_col - 1)
      cur_col++;
    break;
  case SOUTH:
    if (cur_row < m_minefield->n_row - 1)
      cur_row++;
    break;
  case NORTH:
    if (cur_row > 0)
      cur_row--;
    break;
  default: break;
  }
}
