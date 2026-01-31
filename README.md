# UNO Game (C++ Console – 2 Players)

A simple **console-based UNO game** implemented in **C++**, designed for two players.  
The game runs entirely in the terminal and follows the core rules of UNO with turn-based interaction.

---

## Description

This project is a terminal implementation of the classic **UNO card game**.  
It allows two players to play against each other using standard UNO mechanics such as number cards, action cards, and wild cards.  
Game results are automatically stored in a file for record keeping.

---

## Features

- Two-player gameplay (local)
- Console-based interactive interface
- Core UNO rules implemented:
  - Draw cards
  - Skip
  - Reverse
  - Wild cards
- Turn-based logic
- Game results saved to a file (`result.txt`)

---

## Installation

### 1. Clone the repository

git clone https://github.com/tlhasami/UNO_GAME.git
2. Navigate to the project directory
cd UNO_GAME
3. Compile the source code
g++ main.cpp -o uno_game
Usage
Run the game
./uno_game
Gameplay
Follow the on-screen instructions

Players take turns playing cards or drawing from the deck

The first player to run out of cards wins

Game Results
Match results are stored in:

result.txt
Requirements
C++ Compiler (GCC, Clang, or MSVC)

Operating System: Windows / Linux
