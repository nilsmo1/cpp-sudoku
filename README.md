# Sudoku game in C++ using SFML
I like sudoku and felt like playing it - so I made a little game.

## Quick start
SSH
```console
git clone git@github.com:nilsmo1/cpp-sudoku.git 
cd cpp-sudoku/
make run
```
HTTPS
```console
git clone https://github.com/nilsmo1/cpp-sudoku.git
cd cpp-sudoku/
make run
```
Either `make run` or `make && ./sudoku` work the same way.

## Demo
![](https://github.com/nilsmo1/cpp-sudoku/blob/main/sudoku_dark.png)

![](https://github.com/nilsmo1/cpp-sudoku/blob/main/sudoku_light.png)


## Requirements
[__SFML__](https://www.sfml-dev.org/) is required to run this game.

## Controls

Select a cell using the mouse, when a cell is selected you can deselect it with __d__ or move from it with the arrow keys.

Pressing __s__ solves the board.

Pressing __c__ cycles the colorscheme (dark/light).

Pressing __e__ cycles the placement mode, either placement or marking.

Quit the game by pressing __q__ or closing the window!
