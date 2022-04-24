#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include "minefield.h"
#include "utils.h"

class minesweeper_c {
public:
  minesweeper_c(minefield_c* m_minefield);
  ~minesweeper_c();

  int action();

private:
  void update_curser(int dir);

public:
  minefield_c* m_minefield;

private:
  int cur_row;
  int cur_col;

};

#endif
