#ifndef ASSIGNMENT2_19344236_PRINTFILE_H
#define ASSIGNMENT2_19344236_PRINTFILE_H

#include "initialiseBoard.h"
#include <stdio.h>

void fileBoard(square board[BOARD_SIZE][BOARD_SIZE], FILE *fp);
void fileScore(player players[PLAYERS_NUM], FILE *fp);
void fileWinner(player players[PLAYERS_NUM], FILE *fp);
void fileTime(FILE *fp);
void writeFile(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);

#endif
