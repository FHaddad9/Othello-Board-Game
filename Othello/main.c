#include <stdio.h>
#include "initialiseBoard.h"
#include "gameplay.h"
#include "printFile.h"

int main() {
    //declaration of the board
    square board[BOARD_SIZE][BOARD_SIZE];
    player players[PLAYERS_NUM];

    printf("*** Welcome to Othello! ***\n");

    //initialising the players
    initPlayers(players);

    //initialising the board
    initBoard(board);

    //print the board before starting
    printBoard(board);

    //game being played between two players
    playTurns(board, players);

    //writes score details to file
    writeFile(board, players);
}
