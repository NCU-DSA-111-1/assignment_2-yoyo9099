##How to compile
```
gcc ../src/board.c ../src/coord.c ../src/file_processing.c ../src/main.c ../src/stack.c ../inc/board.h ../inc/coord.h ../inc/file_processing.h ../inc/stack.h ../inc/step.h
```
##Useage
**Start new game**
1.Following command can start a new game:
```
–n –s file_name
```
-n: start new game
-s file_name: game record will be saved as "file_name.bin"
2.When the game starts, the following command can use
's' for saving the game
'q' for quitting the game
'b' for taking a move back
Input the coordinate of the chess pice you want to move and input the destination of that chess pice. The following example move the chess pice from "row 5, col 9" to "row 5, col 8":
```
5958
```
The program will check if the move if valid, if not the program will output "invalid input !". The player then have to enter their action again.

If the chess pice can be promoted after the move the player can choose to promote or not

Enter '0' to remain the same
Enter '1' to promote
The game will end when one of the king is captured.

**Load old game**
1.Pass the following argument to load a game:
```
–l file_name
```
-l file_name: load the game record "file_name.bin"
2.After the game is loaded the user can choose action by the following inputs:
'f' for moving to next step
'b' for moving to previous step
'q' for quitting

