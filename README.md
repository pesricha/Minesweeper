# Minesweeper C++ Project

![Game Screen]([image_url](https://github.com/pesricha/Minesweeper/blob/master/image.png))

## Overview

This project is a console-based implementation of the classic game Minesweeper, developed in C++. Minesweeper is a game where players uncover hidden mines on a grid by strategically clicking on cells without detonating any mines.

## Background

Minesweeper has been a popular game enjoyed by many, including the developer of this project, since childhood. Initially, like many players, understanding the game mechanics seemed daunting, often perceived as a game of chance. However, with time and experience, the game's logic became clear.

## Installation
To run this Minesweeper game, you need to download the executable file provided in the repository. 

1. Clone the repository to your local machine.
2. Navigate to the directory containing the executable file.
3. Execute the file to start the game.

## Gameplay

The game is played on a grid of cells, some of which contain hidden mines. The objective is to uncover all cells without detonating any mines. 

- Upon starting the game, the player is presented with a grid where each cell is either hidden or revealed.
- The player selects a cell to uncover. If the selected cell contains a mine, the game ends.
- If the selected cell does not contain a mine, a number is displayed indicating the number of adjacent cells containing mines.
- The player continues selecting cells until either all non-mine cells are uncovered (win) or a cell containing a mine is uncovered (loss).

## Development

This project was developed in C++ as a personal endeavor to understand and implement the game logic. The game loop dynamically updates a character board and mines array, clearing the terminal after each move to display the updated state of the board.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it according to the terms of the license.

