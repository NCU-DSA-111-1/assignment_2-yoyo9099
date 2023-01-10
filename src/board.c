#include "../inc/board.h"
#include "../inc/coord.h"
#include <stdio.h>
#include <stdlib.h>

void printboard(chess board[][SIZE]){//將棋盤畫面輸出
    printf("  1  2  3  4  5  6  7  8  9\n");
    for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if (board[i][j].color == RED){
				printf("\033[31m %s\033[m", chess_name[board[i][j].type]);
			}else if (board[i][j].color == BLUE){
				printf("\033[36m %s\033[m", chess_name[board[i][j].type]);
			}else{
				printf("%s", chess_name[board[i][j].type]);
			}
		}
		printf("%d\n", i + 1);
	}
}

void setchess(chess *target, CHESS_TYPE type, COLOR color){
	target->type = type;
	target->color = color;
}

void initialize(chess board[][SIZE]){//將開局時的棋盤畫面輸出
	COLOR color;
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			setchess(&board[i][j], EMPTY, BLACK);
		}
	}
	for(int i = 0; i < 2; i++){
        if(i == 0){
            color = RED;
        }else{
            color = BLUE;
        }
		int col = 8 * i;
		setchess(&board[col][0], LANCE, color);
		setchess(&board[col][1], KNIGHT, color);
		setchess(&board[col][2], SILVER, color);
		setchess(&board[col][3], GOLD, color);
		setchess(&board[col][4], KING, color);
		setchess(&board[col][5], GOLD, color);
		setchess(&board[col][6], SILVER, color);
		setchess(&board[col][7], KNIGHT, color);
		setchess(&board[col][8], LANCE, color);
		for (int j = 0; j < 9; j++){
			setchess(&board[abs(col - 2)][j], PAWN, color);
		}
	}
	setchess(&board[1][7], BISHOP, RED);
	setchess(&board[1][1], ROOK, RED);
	setchess(&board[7][1], BISHOP, BLUE);
	setchess(&board[7][7], ROOK, BLUE);
}

bool auth(chess board[][SIZE], char *input, COLOR player){ //驗證玩家移動方式是否符合將棋規則
	coord start;
    	coord end;
	int inv;
	int xp;
	int yp;
	start.x = input[0] - '1';
	start.y = input[1] - '1';
	end.x = input[2] - '1';
	end.y = input[3] - '1';
    	if(board[start.y][start.x].color == BLUE){
        	inv = 1;
    	}else{
        	inv = -1;
    	}
	coord vec;
	vec.x = end.x - start.x;
	vec.y = end.y - start.y;
	vec.y *= inv;
	bool re = false;
	if (end.x >= 0 && end.x < SIZE && end.y >= 0 && end.y < SIZE && board[end.y][end.x].color != board[start.y][start.x].color && board[start.y][start.x].color == player){
		switch(board[start.y][start.x].type){
			case EMPTY:
				break;
			case KING:
				if(abs(vec.x) <= 1 && abs(vec.y) <= 1 && abs(vec.x) + abs(vec.y) <= 2 && abs(vec.x) + abs(vec.y) >= 1){
					re = true;
				}
				break;
			case ROOK:
				if(vec.x == 0 && vec.y < 0){
					for(int i = -1; i >= vec.y; i--){
						int tmp = inv * i;
						if(board[start.y + tmp][start.x].color != BLACK){
							break;
						}
					re = true;
					}			
				}else if(vec.x == 0 && vec.y > 0){
					for(int i = -1; i >= vec.y; i--){
						int tmp = inv * -i;
						if(board[start.y + tmp][start.x].color != BLACK){
							break;
						}
					re = true;
					}					
				}else if(vec.y == 0 && vec.x < 0){
					for(int i = -1; i >= vec.x; i--){
						int tmp = inv * i;
						if(board[start.y][start.x + tmp].color != BLACK){
							break;
						}
					re = true;
					}
				}else if(vec.y == 0 && vec.x > 0){
					for(int i = -1; i >= vec.x; i--){
						int tmp = inv * -i;
						if(board[start.y][start.x + tmp].color != BLACK){
							break;
						}
					re = true;
					}
				}
				break;
			case DRAGON:
				if(vec.x == 0 && vec.y < 0){
					for(int i = -1; i >= vec.y; i--){
						int tmp = inv * i;
						if(board[start.y + tmp][start.x].color != BLACK){
							break;
						}
					re = true;
					}			
				}else if(vec.x == 0 && vec.y > 0){
					for(int i = -1; i >= vec.y; i--){
						int tmp = inv * -i;
						if(board[start.y + tmp][start.x].color != BLACK){
							break;
						}
					re = true;
					}					

				}else if(vec.y == 0 && vec.x < 0){
					for(int i = -1; i >= vec.x; i--){
						int tmp = inv * i;
						if(board[start.y][start.x + tmp].color != BLACK){
							break;
						}
					re = true;
					}
				}else if(vec.y == 0 && vec.x > 0){
					for(int i = -1; i >= vec.x; i--){
						int tmp = inv * -i;
						if(board[start.y][start.x + tmp].color != BLACK){
							break;
						}
					re = true;
					}
				}else if(abs(vec.x) == 1 && abs(vec.y) == 1){
						re = true;
					}
				break;
				
			case BISHOP:
				if(abs(vec.x) == abs(vec.y) && vec.x != 0){
					xp = vec.x / abs(vec.x);
					yp = vec.y / abs(vec.y);
					for(int i = 1; i <= vec.x; i++){
						if(board[start.y + (i * yp)][start.x + (i * xp)].color != BLACK){
							re = false;
							break;
						}else{
							re = true;
						}
					}
				}
				break;
							
			case HORSE:
				if(abs(vec.x) == abs(vec.y) && vec.x != 0){
					for(int i = 1; i <= vec.x; i++){
						if(board[start.y + i][start.x + i].color != BLACK){
							re = false;
							break;
						}else{
							re = true;
						}
					}
				}else if(abs(vec.x) <= 1 && abs(vec.y) <= 1 && abs(vec.x) + abs(vec.y) <= 2 && abs(vec.x) + abs(vec.y) >= 1){
					re = true;
				}
				break;
			
			case GOLD:
				if((abs(vec.x + vec.y)==1 && vec.x * vec.y == 0) || (vec.y == -1 && abs(vec.x) == 1)){
					re = true;
				}
			break;
				
			case SILVER:
				if(vec.y == 1 || (vec.y == -1 && vec.x == 1)){
					re = true;
				}
				break;
				
			case UP_SILVER:
				if((abs(vec.x + vec.y)==1 && vec.x * vec.y == 0) || (vec.y == -1 && abs(vec.x) != 1)){
					re = true;
				}
				break;
				
			case KNIGHT:
				if (vec.y == -2 && abs(vec.x) == 1){
					re = true;
				}
				break;
				
			case UP_KNIGHT:
				if((abs(vec.x + vec.y)==1 && vec.x * vec.y == 0) || (vec.y == -1 && abs(vec.x) == 1)){
					re = true;
				}
				break;
				
			case LANCE:
				if(vec.x == 0 && vec.y < 0){
					for(int i = -1; i >= vec.y; i--){
						int tmp = inv * i;
						if(board[start.y + tmp][start.x].color != BLACK){
							break;
						}
					re = true;
					}			
				}
				break;
				
			case UP_LANCE:
				if((abs(vec.x + vec.y)==1 && vec.x * vec.y == 0) || (vec.y == -1 && abs(vec.x) == 1)){
					re = true;
				}
				break;
				
			case PAWN:
				if(vec.y == -1 && vec.x==0){
					re = true;
				}
				break;
				
			case UP_PAWN:
				if((abs(vec.x + vec.y)==1 && vec.x * vec.y == 0) || (vec.y == -1 && abs(vec.x) == 1)){
					re = true;
				}
				break;

			default:
			
				break;
		}
	}
	return re;
}

void move(chess board[][SIZE],coord start,coord end,short promote){
	setchess(&board[end.y][end.x], board[start.y][start.x].type + promote, board[start.y][start.x].color);
	setchess(&board[start.y][start.x], EMPTY, BLACK);
}

bool check_promote(CHESS_TYPE type, coord start, coord end, COLOR player){
	if(type==ROOK || type==BISHOP || type==SILVER || type==KNIGHT || type==LANCE || type==PAWN){
		if ((player==BLUE && (start.y<=2 || end.y<=2)) || (player==RED && (start.y>=6 || end.y>=6) ) ){
			return true;
		}
	}
	return false;	
}

void lastmove(chess board[][SIZE], step back, COLOR player){
	move(board, back.end, back.start, -1*back.promote);
	if(back.capture != EMPTY){
		setchess(&board[back.end.y][back.end.x], back.capture, player);	
	}	
}
