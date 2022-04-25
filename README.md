# Minesweeper

- This repo is made just for fun :)

## How To Use
```
mkdir build
cd build
cmake ..
make -j4
make install # install path is ../bin
./minesweeper easy # or medium or hard
```
- There are three difficulties, easy, medium, hard.
- Easy: 9x9, number of mines = 10
- Medium: 16x16, number of mines = 40
- Hard: 30x16, number of mines = 99

- Arrow keys
  - `h`/`j`/`k`/`l` : left / down / up / right (same as Vim)
  - `q`: left click
  - `w`: right click (check as possible mine)
