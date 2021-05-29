#ifndef ASSIGNMENT2_19344236_INITIALISEBOARD_H
#define ASSIGNMENT2_19344236_INITIALISEBOARD_H

#define BOARD_SIZE 8
#define PLAYERS_NUM 2

//colours that a square can have
typedef enum colour {
    WHITE,
    BLACK,
    NEUTRAL
}colour;

//player details
typedef struct player{
    colour playerColour;
    char name[20];
    int piecesOnBoard;
    int piecesOnHand;
}player;

//types that a square can have
typedef enum squareType {
    VALID,
    INVALID
}squareType;

//square details whether it is valid/invalid and white/black
typedef struct square {
    squareType type;
    colour squareColour;
}square;

void initPlayers(player players[PLAYERS_NUM]);
void initBoard(square board [BOARD_SIZE][BOARD_SIZE]);
void printBoard(square board[BOARD_SIZE][BOARD_SIZE]);

#endif
