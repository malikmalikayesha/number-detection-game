# Number Detection Game

Welcome to the Number Detection game project! This console-based game challenges players to guess the position of a hidden number in a grid. With three different levels and a strategic use of data structures, this game offers an engaging experience for users.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Levels](#levels)
- [Data Structures](#data-structures)
- [How to Play](#how-to-play)
- [Project Presentation](#project-presentation)
- [Installation](#installation)
- [Contributing](#contributing)

## Overview

In the Number Detection game, players are presented with a grid of varying sizes (3x3, 5x5, and 7x7) based on the selected level. The objective is to guess the position of a hidden number behind the grid. Players are given three lives, and a hint is provided through a change in the color of the grid. The numbers are gradually revealed as the player guesses the correct positions.

## Features

- Three levels of difficulty (3x3, 5x5, and 7x7 grids)
- Lives system implemented using stacks
- Dynamic grid color change for hinting
- Gradual number revelation as the player makes correct guesses
- Flexible gameplay with the option to choose any level
- Scoring system based on the number of attempts
- Hint system to narrow down the search after the first attempt

## Levels

1. **Level 1 (3x3 Grid):** Beginner level with a smaller grid size.
2. **Level 2 (5x5 Grid):** Intermediate level with a moderately sized grid.
3. **Level 3 (7x7 Grid):** Advanced level with a larger grid for seasoned players.

Players can choose any level or progress through them sequentially for an increasing challenge.

## Data Structures

The project utilizes the following data structures:

1. **Arrays:** Used for managing stacks.
2. **Linked List:** Used for managing queues.
3. **Stacks:** Implemented for managing lives. Each level has its own stack.
4. **Queues:** Employed for random number generation that determines the hidden numbers behind the grid.
5. **Vectors:** Used for various dynamic data storage needs.

## How to Play

1. Choose a level (1, 2, or 3) or follow the sequence from 1 to 3 for increasing difficulty.
2. Guess the position of the hidden number in the grid.
3. Receive hints through changes in grid color.
4. Use the provided lives wisely; three incorrect guesses lead to game over.
5. After the first attempt, the game provides a hint to the user to narrow down the search. The cells that might have the target number behind them are subtly highlighted with a different color, making it easier for the player to make informed choices in the subsequent attempts. Use this hint wisely to maximize your score.
6. Earn points based on your attempts: 5 points for the first attempt, 3 points for the second, and 2 points for the third.
7. Enjoy the challenge and have fun!

## Project Presentation

Explore the inner workings of the code and see the game in action! Check out the [Presentation folder](Presentation/) for detailed insights and a video demonstration of the game output.

## Installation

1. Clone the repository to your local machine.
2. Compile and run the game using your preferred C++ compiler.
3. Follow the on-screen instructions to play the game.

## Contributing

Contributions are welcome! If you'd like to contribute, please follow the guidelines in the CONTRIBUTING.md file.

Enjoy the Number Detection game!
