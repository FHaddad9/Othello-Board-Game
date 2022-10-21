# Othello Board Game

This is a C project made from the 2 player board game Othello.

## Description

- Players can choose to be **white** or **black** piece
- 8x8 GUI board
- Board shows which pieces are occupied by first letter of colour; **| b |** *or* **| w |**
- Four squares automatically occupied by 2 of each player's pieces

## Details

- Players enter details: names, colour choice
- Each player's pieces on board and hand implemented
- Board square is checked based on direction of corresponding pieces
    - Structs are used for square colour and if it's valid
    - Array loop checks whether a square contains an opposing colour
- Win condition calculated by how many coloured pieces on the board
- Game ends with text file printing final board, winning player and time


## Example Image

![Image of Winning Board](/Picture/Othello.png)
