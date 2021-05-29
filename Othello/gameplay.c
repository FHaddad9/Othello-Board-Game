#include "gameplay.h"
#include <stdio.h>
#include <string.h>

int turn = 1;
int win = 1;
//placeholders if player has found a valid move
int ownPiece = 0;
int checkValid = 0;
//keeps score
int score = 0;
//determines if player can make a move during their turn
int possibleMove = 0;
//if the move is valid, the index of the last piece is saved
int yindex;
int xindex;


//prints the player's score
void printScore(player players[PLAYERS_NUM]){
    printf("\nScore: %s (Black) %d:%d %s (White)", players[0].name, players[0].piecesOnBoard, players[1].piecesOnBoard,
            players[1].name);
    printf("\nPieces: %s (Black) %d:%d %s (White)\n", players[0].name, players[0].piecesOnHand, players[1].piecesOnHand,
           players[1].name);
}

//function for playing the game
void playTurns(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]) {

    int xCoordinate;
    int yCoordinate;

    char move[10];

    while (win != 0) {
        while (turn != 0) {
            printf("\n%s's turn (Black):\n", players[0].name);
            searchPossibleMoves(board, players, 0);
            //if there are no possible moves to play, player can pass
            if (possibleMove == 0) {
                printf("enter 'p' to pass: ");
                scanf("%s", move);
                if (strcmp(move, "p") == 0) {
                    turn = 0;
                } else {
                    printf("Invalid move, try again!\n");
                }
                //or else, player enters co-ordinates of piece they want to place
            } else {
                printf("Enter move to make: ");
                scanf("%s", move);
                if ((move[1] >= 49 && move[1] <= 56) && (move[0] >= 97 && move[0] <= 104)) {
                    xCoordinate = move[1] - 49;
                    yCoordinate = move[0] - 97;
                    makeMove(board, players, xCoordinate, yCoordinate, 0);
                } else {
                    printf("Invalid move, try again!\n");
                }
            }
        }

        //prints out board and score each time player finishes turn
        printBoard(board);
        printScore(players);
        turn = 1;
        ownPiece = 0;

        //checks if a winner has been found
        determineWinner(board, players);
        if(win == 0){
            break;
        }

        while (turn != 0) {
            printf("\n%s's turn (White):\n", players[1].name);
            searchPossibleMoves(board, players, 1);
            if (possibleMove == 0) {
                printf("enter 'p' to pass: ");
                scanf("%s", move);
                if (strcmp(move, "p") == 0) {
                    turn = 0;
                } else {
                    printf("Invalid move, try again!\n");
                }
            } else {
                printf("Enter move to make: ");
                scanf("%s", move);
                if ((move[1] >= 49 && move[1] <= 56) && (move[0] >= 97 && move[0] <= 104)) {
                    xCoordinate = move[1] - 49;
                    yCoordinate = move[0] - 97;
                    makeMove(board, players, xCoordinate, yCoordinate, 1);
                } else {
                    printf("Invalid move, try again!\n");
                }
            }
        }

        printBoard(board);
        printScore(players);
        turn = 1;
        ownPiece = 0;

        determineWinner(board, players);
    }
}

//function determines the winner of the game
void determineWinner(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    int boardCount = 0;
    int finish = 0;

    //checks if all 64 squares are invalid
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type == INVALID)
                boardCount++;
        }
    }

    //checks if both players have no more valid moves
    searchPossibleMoves(board, players, 0);
    searchPossibleMoves(board, players, 1);
    if(possibleMove == 0){
        finish++;
    }

    //determines winner if board is full, or no more pieces can be placed
    if (boardCount == 64 || finish != 0) {
        if (players[0].piecesOnBoard > players[1].piecesOnBoard) {
            printf("\n%s (BLACK) has won the game", players[0].name);
        } else if (players[1].piecesOnBoard > players[0].piecesOnBoard) {
            printf("\n%s (WHITE) has won the game", players[1].name);
        } else {
            printf("\nDraw!");
        }
        win = 0;
    }
}

//function to change valid square to player's colour
void changeYourPiece(int x, int y){
    ownPiece = 1;
    score++;
    xindex = x;
    yindex = y;
    checkValid = 1;
}

//function to change opponent's pieces to the player's colours
void changeOppPiece(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int x, int y, int playerNum){
    board[x][y].squareColour = players[playerNum].playerColour;
    board[x][y].type = INVALID;
    score++;
}

//makes move from co-ordinates entered
void makeMove(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int x, int y, int playerNum){
    enum colour pColour = NEUTRAL;
    enum colour oppColour = NEUTRAL;

    checkValid = 0;
    score = 0;
    xindex = 0;
    yindex = 0;

    int opponentNum;
    int yinc = 1;

    if (players[playerNum].playerColour == BLACK) {
        pColour = BLACK;
        oppColour = WHITE;
        opponentNum = 1;
    } else if (players[playerNum].playerColour == WHITE) {
        pColour = WHITE;
        oppColour = BLACK;
        opponentNum = 0;
    }

    //as long as the square isn't occupied
    if(board[x][y].type != INVALID) {
        //check from left to right
        if (board[x][y + 1].squareColour == oppColour) {
            for (int i = y + 1; i < BOARD_SIZE; i++) {
                if (board[x][i].squareColour == pColour) {
                    changeYourPiece(0, i);
                    break;
                }
            }
            if (checkValid == 1) {
                for (int i = y + 1; i < yindex; i++) {
                    changeOppPiece(board, players, x, i, playerNum);
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x][y - 1].squareColour == oppColour) {     //checks from right to left
            for (int i = y - 1; i > 0; i--) {
                if (board[x][i].squareColour == pColour) {
                    changeYourPiece(0, i);
                    break;
                }
            }
            if (checkValid == 1) {
                for (int i = y - 1; i > yindex; i--) {
                    changeOppPiece(board, players, x, i, playerNum);
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x + 1][y].squareColour == oppColour) {     //checks from up to down
            for (int i = x + 1; i < BOARD_SIZE; i++) {
                if (board[i][y].squareColour == pColour) {
                    changeYourPiece(i, 0);
                    break;
                }
            }
            if (checkValid == 1) {
                for (int i = x + 1; i < xindex; i++) {
                    changeOppPiece(board, players, i, y, playerNum);
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x - 1][y].squareColour == oppColour) {     //checks from down to up
            for (int i = x - 1; i > 0; i--) {
                if (board[i][y].squareColour == pColour) {
                    changeYourPiece(i, 0);
                    break;
                }
            }
            if (checkValid == 1) {
                for (int i = x - 1; i > xindex; i--) {
                    changeOppPiece(board, players, i, y, playerNum);
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x + 1][y + 1].squareColour == oppColour) {     //checks from left to right up diag
            for (int i = x + 1; i < BOARD_SIZE; i++) {
                int j = y + yinc;
                if (board[i][j].squareColour == pColour) {
                    changeYourPiece(i, j);
                    break;
                } else{
                    yinc++;
                }
            }
            if (checkValid == 1) {
                for (int i = x + 1; i < xindex; i++) {
                    for (int j = y + 1; j < yindex; j++) {
                        changeOppPiece(board, players, i, j, playerNum);
                    }
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x - 1][y - 1].squareColour == oppColour) {     //checks from right to left down diag
            for (int i = x - 1; i > 0; i--) {
                int j = y - yinc;
                if (board[i][j].squareColour == pColour) {
                    changeYourPiece(i, j);
                    break;
                } else{
                    yinc++;
                }
            }
            if (checkValid == 1) {
                for (int i = x - 1; i > xindex; i--) {
                    for (int j = y - 1; j > yindex; j--) {
                        changeOppPiece(board, players, i, j, playerNum);
                    }
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x + 1][y - 1].squareColour == oppColour) {     //checks from left to right down diag
            for (int i = x + 1; i < BOARD_SIZE; i++) {
                int j = y - yinc;
                if (board[i][j].squareColour == pColour) {
                    changeYourPiece(i, j);
                    break;
                } else{
                    yinc++;
                }
            }
            if (checkValid == 1) {
                for (int i = x + 1; i < xindex; i++) {
                    for (int j = y - 1; j > yindex; j--) {
                        changeOppPiece(board, players, i, j, playerNum);
                    }
                }
                players[playerNum].piecesOnHand--;
            }
        } else if (board[x - 1][y + 1].squareColour == oppColour) {     //checks from right to left up diag
            for (int i = x - 1; i > 0; i--) {
                int j = y + yinc;
                if (board[i][j].squareColour == pColour) {
                    changeYourPiece(i, j);
                    break;
                } else{
                    yinc++;
                }
            }
            if (checkValid == 1) {
                for (int i = x - 1; i > xindex; i--) {
                    for (int j = y + 1; j < yindex; j++) {
                        changeOppPiece(board, players, i, j, playerNum);
                    }
                }
                players[playerNum].piecesOnHand--;
            }
        }

        //changes colour of piece placed, changes score and sets square to occupied
        if (ownPiece == 1) {
            board[x][y].squareColour = pColour;
            board[x][y].type = INVALID;
            players[playerNum].piecesOnBoard += score;
            players[opponentNum].piecesOnBoard -= (score - 1);
            turn = 0;
        } else {
            printf("Invalid Entry, try again!\n");
            turn = 1;
        }
    } else{
        printf("Square already occupied, try again!\n");
        turn = 1;
    }
}

//Similar to makeMove function, increments an int 'possibleMove' if a move can be made
//this is done to check if the player can't make any moves during their turn
void searchPossibleMoves(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int playerNum){
    enum colour pColour = NEUTRAL;
    enum colour oppColour = NEUTRAL;

    int yinc = 1;

    if (players[playerNum].playerColour == BLACK) {
        pColour = BLACK;
        oppColour = WHITE;
    } else if (players[playerNum].playerColour == WHITE) {
        pColour = WHITE;
        oppColour = BLACK;
    }
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y].type != INVALID) {
                if (board[x][y + 1].squareColour == oppColour) {
                    for (int i = y + 1; i < BOARD_SIZE; i++) {
                        if (board[x][y].squareColour == pColour) {
                            possibleMove++;
                        }
                    }
                } else if (board[x][y - 1].squareColour == oppColour) {
                    for (int i = y - 1; i > 0; i--) {
                        if (board[x][i].squareColour == pColour) {
                            possibleMove++;
                        }
                    }
                } else if (board[x + 1][y].squareColour == oppColour) {
                    for (int i = x + 1; i < BOARD_SIZE; i++) {
                        if (board[i][y].squareColour == pColour) {
                            possibleMove++;
                        }
                    }
                } else if (board[x - 1][y].squareColour == oppColour) {
                    for (int i = x - 1; i > 0; i--) {
                        if (board[i][y].squareColour == pColour) {
                            possibleMove++;
                        }
                    }
                } else if (board[x + 1][y + 1].squareColour == oppColour) {
                    for (int i = x + 1; i < BOARD_SIZE; i++) {
                        int j = y + yinc;
                        if (board[i][j].squareColour == pColour) {
                            possibleMove++;
                        } else{
                            yinc++;
                        }
                    }
                } else if (board[x - 1][y - 1].squareColour == oppColour) {
                    for (int i = x - 1; i > 0; i--) {
                        int j = y - yinc;
                        if (board[i][j].squareColour == pColour) {
                            possibleMove++;
                        } else{
                            yinc++;
                        }
                    }
                } else if (board[x + 1][y - 1].squareColour == oppColour) {
                    for (int i = x + 1; i < BOARD_SIZE; i++) {
                        int j = y - yinc;
                        if (board[i][j].squareColour == pColour) {
                            possibleMove++;
                        } else{
                            yinc++;
                        }
                    }
                } else if (board[x - 1][y + 1].squareColour == oppColour) {
                    for (int i = x - 1; i > 0; i--) {
                        int j = y + yinc;
                        if (board[i][j].squareColour == pColour) {
                            possibleMove++;
                        } else {
                            yinc++;
                        }
                    }
                }
            }
        }
    }
}