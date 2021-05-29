#ifndef ASSIGNMENT2_19344236_GAMEPLAY_H
#define ASSIGNMENT2_19344236_GAMEPLAY_H

#include "initialiseBoard.h"

void printScore(player players[PLAYERS_NUM]);
void playTurns(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);
void determineWinner(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);
void changeYourPiece(int x, int y);
void changeOppPiece(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int x, int y, int playerNum);
void searchPossibleMoves(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int playerNum);
void makeMove(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int x, int y, int playerNum);

#endif
