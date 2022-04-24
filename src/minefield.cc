#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdlib.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include "minefield.h"

minefield_c::minefield_c(int n_row, int n_col, int n_mine) {
  this->n_row = n_row;
  this->n_col = n_col;
  this->n_mine = n_mine;
  done_th = n_row * n_col - n_mine;
  cur_done_n = 0;

  init();
}

minefield_c::~minefield_c() {
  for (int i = 0; i < n_row; i++) {
    free(minefield[i]);
    free(hiddenfield[i]);
    free(donefield[i]);
  }
  free(minefield);
  free(hiddenfield);
  free(donefield);
}

int minefield_c::check_no_mine(int m, int n) {
  int done;
  if (is_mine(m, n)) {
    //bomb();
    return -1; // bomb!
  }

  occupy_area(m, n);
  done = (int) check_done();
  return done;
}

void minefield_c::check_mine(int m, int n) {
  // toggle
  std::cout << possiblefield[0][0] << std::endl;
  possiblefield[m][n] = !possiblefield[m][n];
  donefield[m][n] = !donefield[m][n];
}

bool minefield_c::is_mine(int m, int n) {
  return minefield[m][n];
}

void minefield_c::init() {
  init_minefield();
  init_hiddenfield();
  init_donefield();
  init_possiblefield();
}

void minefield_c::init_minefield() {
  minefield = (bool**) malloc(n_row * sizeof(bool*));
  for (int i = 0; i < n_row; i++) {
    minefield[i] = (bool*) malloc(n_col * sizeof(bool));
  }

  // random mine generation
  unsigned int now = (unsigned int) time(nullptr);
  unsigned int seed = 8253729 * now + 2396403;
  srand(seed);

  int i = 0;
  //for (int i = 0; i < n_mine; i++) {
  while (i < n_mine) {
    int rand_num = rand() % (n_row * n_col);
    int m_row = rand_num / n_col;
    int m_col = rand_num % n_col;
    if (!minefield[m_row][m_col]) {
      minefield[m_row][m_col] = true;
      i++;
    }
  }
}

void minefield_c::init_hiddenfield() {
  hiddenfield = (int**) malloc(n_row * sizeof(int*));
  for (int i = 0; i < n_row; i++) {
    hiddenfield[i] = (int*) malloc(n_col * sizeof(int));
  }

  // hiddenfield generation
  // 1) -1: mine
  // 2) > 0: # of mines in local 3x3 field
  for (int i = 0; i < n_row; i++) {
    for (int j = 0; j < n_col; j++) {
      hiddenfield[i][j] = get_num_detected_mines(i, j);
    }
  }
}

void minefield_c::init_donefield() {
  donefield = (bool**) malloc(n_row * sizeof(bool*));
  for (int i = 0; i < n_row; i++) {
    donefield[i] = (bool*) malloc(n_col * sizeof(bool));
  }

  for (int i = 0; i < n_row; i++) {
    for (int j = 0; j < n_col; j++) {
      donefield[i][j] = false;
    }
  }
}

void minefield_c::init_possiblefield() {
  possiblefield = (bool**) malloc(n_row * sizeof(bool*));
  for (int i = 0; i < n_row; i++) {
    possiblefield[i] = (bool*) malloc(n_col * sizeof(bool));
  }

  for (int i = 0; i < n_row; i++) {
    for (int j = 0; j < n_col; j++) {
      possiblefield[i][j] = false;
    }
  }
}

void minefield_c::occupy_area(int m, int n) {
  //assert(is_mine == false);  
  if (!donefield[m][n]) {
    donefield[m][n] = true;
    cur_done_n++;
    if (hiddenfield[m][n] > 0) {
      return;
    }
  }
  else return;

  for (int i = -1; i <= 1; i++) {
    int m_row = m + i;
    for (int j = -1; j <= 1; j++) {
      int m_col = n + j;
      if (i == 0 && j == 0) continue; // do not cover myself -> inifinite loop
      if (is_valid(m_row, m_col)) {
        occupy_area(m_row, m_col);
      }
    }
  }
}

int minefield_c::get_num_detected_mines(int m, int n) {
  if (minefield[m][n]) return -1;

  int tot_mines = 0;
  for (int i = -1; i <= 1; i++) {
    int m_row = m + i;
    for (int j = -1; j <= 1; j++) {
      int m_col = n + j;
      if (is_valid(m_row, m_col)) {
        if (minefield[m_row][m_col]) {
          tot_mines++;
        }
      }
    }
  }
  return tot_mines;
}

bool minefield_c::check_done() {
  return (cur_done_n == done_th);
}

bool minefield_c::is_valid(int m, int n) {
  return (m >= 0 && n >= 0 && m < n_row && n < n_col);
}

void minefield_c::disp_minefield(int cur_row, int cur_col) {
  system("clear");

  std::cout << std::endl;
  std::cout << "********************* MINESWEEPER *********************" << std::endl;

  // top outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;

  for (int i = 0; i < n_row; i++) {
    std::cout << "|";
    for (int j = 0; j < n_col; j++) {
      if (cur_row == i && cur_col == j) {
        std::cout << "V";
        continue;
      }

      if (donefield[i][j]) {
        if (possiblefield[i][j]) { // checked as mine-possible
          std::cout << "?";
        }
        else if (hiddenfield[i][j] > 0) {
          std::cout << hiddenfield[i][j];
        }
        else if (hiddenfield[i][j] == 0) {
          std::cout << " ";
        }
      }
      else {
        std::cout << " ";
      }

    }
    std::cout << "|" << std::endl;
  }

  // bottom outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
}

void minefield_c::bomb(int m, int n) {
  system("clear");

  std::cout << std::endl;
  std::cout << "********************* MINESWEEPER *********************" << std::endl;

  // top outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;

  for (int i = 0; i < n_row; i++) {
    std::cout << "|";
    for (int j = 0; j < n_col; j++) {
      if (m == i && n == j) {
        std::cout << "$";
        continue;
      }
      if (possiblefield[i][j]) { // checked as mine-possible
        std::cout << "?";
      }
      else if (minefield[i][j]) {
        std::cout << "*";
      }
      else if (donefield[i][j]) {
        if (hiddenfield[i][j] > 0) {
          std::cout << hiddenfield[i][j];
        }
        else if (hiddenfield[i][j] == 0) {
          std::cout << " ";
        }
      }
      else {
        std::cout << " ";
      }

    }
    std::cout << "|" << std::endl;
  }

  // bottom outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;
  std::cout << "********************* BOMB!! *********************" << std::endl;
}

void minefield_c::done() {
  system("clear");

  std::cout << std::endl;
  std::cout << "********************* MINESWEEPER *********************" << std::endl;

  // top outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;

  for (int i = 0; i < n_row; i++) {
    std::cout << "|";
    for (int j = 0; j < n_col; j++) {
      if (minefield[i][j]) {
        std::cout << "*";
      }
      else if (hiddenfield[i][j] > 0) {
        std::cout << hiddenfield[i][j];
      }
      else {
        std::cout << " ";
      }
    }
    std::cout << "|" << std::endl;
  }

  // bottom outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;
  std::cout << "********************* DONE!! *********************" << std::endl;
}

void minefield_c::disp_hiddenfield() {

  std::cout << std::endl;
  std::cout << "********************* MINESWEEPER *********************" << std::endl;

  // top outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;

  for (int i = 0; i < n_row; i++) {
    std::cout << "|";
    for (int j = 0; j < n_col; j++) {
      if (minefield[i][j]) {
        std::cout << "?";
      }
      else if (hiddenfield[i][j] > 0) {
        std::cout << hiddenfield[i][j];
      }
      else {
        std::cout << " ";
      }
    }
    std::cout << "|" << std::endl;
  }

  // bottom outline
  for (int i = 0; i < n_col + 2; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

