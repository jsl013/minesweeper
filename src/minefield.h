#ifndef __MINEFIELD_H__
#define __MINEFIELD_H__

#include "utils.h"

class minefield_c {
public:
  minefield_c(int n_row, int n_col, int n_mine);
  ~minefield_c();

  int check_no_mine(int m, int n);
  void check_mine(int m, int n);
  int check_neighbors(int m, int n);
  void init();

  // display
  void bomb(int cur_row, int cur_col);
  void disp_minefield(int cur_row, int cur_col);
  void disp_hiddenfield();
  void done();

private:
  void init_minefield();
  void init_hiddenfield();
  void init_donefield();
  void init_possiblefield();
  void occupy_area(int m, int n); // if hiddenfield[m][n] == 0, occupy the island
  bool is_mine(int m, int n);
  bool is_valid(int m, int n);

  int get_num_detected_mines(int m, int n);
  bool check_done();

public:
  int n_row;
  int n_col;
  int n_mine;
  int done_th;

  int cur_done_n;
  bool** minefield;
  int** hiddenfield;
  bool** donefield;
  bool** possiblefield;
};

#endif
