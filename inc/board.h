#ifndef BOARD_H
#define BOARD_H
#define SIZE 9
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "coord.h"
#include "step.h"
typedef enum {BLUE, RED, BLACK}COLOR;
typedef enum {KING, ROOK, DRAGON, BISHOP, HORSE, GOLD, SILVER, UP_SILVER, KNIGHT, UP_KNIGHT, LANCE, UP_LANCE, PAWN, UP_PAWN, EMPTY}CHESS_TYPE;
static const char *chess_name[] = {"王","飛","龍","角","馬","金","銀","全","桂","圭","香","杏","步","と","   "};

typedef struct chess_sct{
    CHESS_TYPE type;
    COLOR color;
}chess;

void printboard(chess board[][SIZE]);
void setchess(chess *target, CHESS_TYPE type, COLOR color);
void initialize(chess board[][SIZE]);
bool auth(chess board[][SIZE], char *input, COLOR player);
void move(chess board[][SIZE], coord start, coord end, short promote);
bool check_promote(CHESS_TYPE type,coord start,coord end,COLOR player);
void lastmove(chess board[][SIZE],step back,COLOR player);
#endif
