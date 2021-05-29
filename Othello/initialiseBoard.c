#include <stdio.h>
#include "initialiseBoard.h"

//initialising players, filing out their details
void initPlayers(player players[PLAYERS_NUM]){

    printf("Input player 1's name (BLACK): ");
    scanf("%s", players[0].name);
    players[0].playerColour=BLACK;
    players[0].piecesOnBoard=2;
    players[0].piecesOnHand=30;

    printf("Input player 1's name (WHITE): ");
    scanf("%s", players[1].name);
    players[1].playerColour=WHITE;
    players[1].piecesOnBoard=2;
    players[1].piecesOnHand=30;

    printf("\n");
}

//sets square invalid to land a piece
setInvalid(square * s){
    s->type = INVALID;
}

//sets square valid to land a piece
setValid(square * s){
    s->type = VALID;
}

//set square to white colour
setWhite(square * s){
    s->squareColour = WHITE;
}

//set square to black colour
setBlack(square * s){
    s->squareColour = BLACK;
}

//set square to neutral colour
setNeutral(square * s){
    s->squareColour = NEUTRAL;
}

//initializes the board
void initBoard(square board [BOARD_SIZE][BOARD_SIZE]) {

    //puts 2 white and black pieces to middle of board
    //rest of board is empty and valid to place piece
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == 3 && j == 3) {
                setWhite(&board[i][j]);
                setInvalid(&board[i][j]);
            } else if (i == 3 && j == 4) {
                setBlack(&board[i][j]);
                setInvalid(&board[i][j]);
            } else if (i == 4 && j == 4) {
                setWhite(&board[i][j]);
                setInvalid(&board[i][j]);
            } else if (i == 4 && j == 3) {
                setBlack(&board[i][j]);
                setInvalid(&board[i][j]);
            } else {
                setValid(&board[i][j]);
                setNeutral(&board[i][j]);
            }
        }
    }
}

//prints board
void printBoard(square board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n\t");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" ___");
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 8; j <= BOARD_SIZE; j++){
            printf("\n%d\t", i+1);
        }
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j].squareColour == BLACK){
                printf("| B ");
            }
            else if(board[i][j].squareColour == WHITE){
                printf("| W ");
            }
            else if (board[i][j].type == VALID) {
                printf("|   ");
            }
        }

        printf("|\n");
        printf("\t");

        for (int k = 0; k < BOARD_SIZE; k++) {
            printf(" ---");
        }
    }
    printf("\n\t  a\t  b\t  c\t  d\t  e\t  f\t  g\t  h");
}
