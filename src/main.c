#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "../inc/board.h"
#include "../inc/coord.h"
#include "../inc/stack.h"
#define INPUT_SIZE 7
#define MAX_FILENAME_SIZE 30

chess board[SIZE][SIZE];
stack *record=NULL;
typedef enum {NG, LOAD}MODE;
int main(int argc, char *argv[]) {
	initialize(board);
	printboard(board);
	coord start,end;
	int turn = 0;
	COLOR player = BLUE;
	MODE mode;
	char input[INPUT_SIZE];
	char file_name[MAX_FILENAME_SIZE];
	char opt;
	/*get parameters*/
	while((opt = getopt(argc,argv,"ns:l:"))!=-1){
		switch(opt){ //select mode
			case 'n':
				mode = NG;//new game mode
				break;
			case 'l':
				mode = LOAD;//load mode
				strncpy(file_name, optarg, MAX_FILENAME_SIZE);
				break;
			case 's':
				strncpy(file_name, optarg, MAX_FILENAME_SIZE);
				break;
			default:
				break;
		}
	}
	switch(mode){
		case LOAD: //load
		{
			stack *pre_record=NULL;
			read_file(&record, file_name);
			while(true){
				/*get control input*/
				printf("foward = d , back = a : ");
				scanf(" %s",input);
				step now;
				/*take action*/
				if(input[0]== 'd' && !isEmpty(record)){ //move to next step
					now = pop(&record);
					push(&pre_record, now);
					move(board, now.start, now.end, now.promote);
					player = !player;
					printboard(board);
				}else if(input[0]=='a' && !isEmpty(pre_record)){ //move to previous step
					now=pop(&pre_record);
					push(&record,now);
					lastmove(board,now,player);
					player = !player;
					printboard(board);
				}else if(input[0]=='q'){ //quit
					break;
				}
				else{
					printf("invalid\n");
				}
			}
			break;
		}
		case NG: //newgame
			while(true){
				printf("player %d : ",player);
				fgets(input, INPUT_SIZE, stdin);
				if(input[0] == 's'){ //save file
					write_file(record, file_name);
				}else if(input[0] =='b' && turn > 0){ //back
					step back = pop(&record);
					lastmove(board, back, player);
					player = !player;
					turn -= 1;
					printboard(board);
				}else if(input[0] == 'q'){ //quit
					break;
				}else{ //regular move
					/*check valid move*/
					if(auth(board, input, player)){
						start.x = input[0] - '1';
						start.y = input[1] - '1';
						end.x = input[2] - '1';
						end.y = input[3] - '1';
						bool can_promote = false;
						/*check if the chess pice can be promoted*/
						if(check_promote(board[start.y][start.x].type, start, end, player)){
							/*ask if the player want to promote the chess pice*/
							printf("Do you want to promote %s ? Yes:1 No:0 :", chess_name[board[start.y][start.x].type]);
							fgets(input, INPUT_SIZE, stdin);
							if(input[0] == '1')can_promote = true;
						}
						CHESS_TYPE capture = board[end.y][end.x].type;
						move(board, start, end, can_promote); //move the chess pice
						step now={.start = start,.end = end,.promote = can_promote,.capture = capture};
						push(&record,now); //record step
						printboard(board);
						if(capture == KING){ //determine if the king has been capture
							printf("Player %d wins \n",player);
							break;
						}
						
						turn += 1;
						player = !player;
					}else{
						printf("invalid input !\n");
					}
				}
			}
			break;
		default:
			break;
	}
	return 0;
}
