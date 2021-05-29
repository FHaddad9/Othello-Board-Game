#include "printFile.h"
#include <stdio.h>
#include <time.h>

//prints the board to file
void fileBoard(square board[BOARD_SIZE][BOARD_SIZE], FILE *fp){

    fprintf(fp, "\nBoard: \n\t");
    for (int i = 0; i < BOARD_SIZE; i++) {
        fprintf(fp, " ___");
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 8; j <= BOARD_SIZE; j++){
            fprintf(fp, "\n%d\t", i+1);
        }
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j].squareColour == BLACK){
                fprintf(fp, "| B ");
            }
            else if(board[i][j].squareColour == WHITE){
                fprintf(fp, "| W ");
            }
            else if (board[i][j].type == VALID) {
                fprintf(fp, "|   ");
            }
        }

        fprintf(fp, "|\n");
        fprintf(fp, "\t");

        for (int k = 0; k < BOARD_SIZE; k++) {
            fprintf(fp, " ---");
        }
    }
    fprintf(fp, "\n\t  a   b   c   d   e   f   g   h");

}

//prints the score to file
void fileScore(player players[PLAYERS_NUM], FILE *fp){
    fprintf(fp, "\nScore: %s (Black) %d:%d %s (White)", players[0].name, players[0].piecesOnBoard, players[1].piecesOnBoard,
           players[1].name);
    fprintf(fp, "\nPieces: %s (Black) %d:%d %s (White)\n", players[0].name, players[0].piecesOnHand, players[1].piecesOnHand,
           players[1].name);
}

//prints the winner of the game to file
void fileWinner(player players[PLAYERS_NUM], FILE *fp){
    if (players[0].piecesOnBoard > players[1].piecesOnBoard) {
        fprintf(fp, "%s (BLACK) has won the game\n", players[0].name);
    } else if (players[1].piecesOnBoard > players[0].piecesOnBoard) {
        fprintf(fp, "%s (WHITE) has won the game\n", players[1].name);
    } else {
        fprintf(fp, "Draw!\n");
    }
}

//prints the time and date of the finished game to file
void fileTime(FILE *fp){
    time_t timeNow;
    time(&timeNow);

    fprintf(fp, "Time and date: %s\n", ctime(&timeNow));
}

void writeFile(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    FILE * fp;

    fp = fopen("othello-results.txt", "w");

    fprintf(fp, "*** Results of Game! ***\n");

    fileTime(fp);

    fileWinner(players, fp);

    fileScore(players, fp);

    fileBoard(board, fp);

    fclose(fp);
}