# CODING-SAMURAI-INTERNSHIP-TASK
This repository will host the tasks I completed with coding samurai during my C++ internship

I completed task 2, a tic-tac-toe game with two players, and you can restart the game. I implemented this by using OpenGL libraries to help me create an easy and user-friendly UI for the players.

I started by declaring 4 main variables
```cpp
int playerturn; // if it is 1, then it's the first player's turn. if it is 2, then it's the second player's turn
int matrix[3][3]; // Grid represented in a 2D matrix
int result; // if it is 0, then it's a draw; if it is 1, then Player X wins; if it is 2, then Player O wins
bool gameOver; // if it is false, then it's not game over. if it is true, then it's game over
```
