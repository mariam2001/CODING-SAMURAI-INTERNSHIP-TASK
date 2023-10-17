# CODING-SAMURAI-INTERNSHIP-TASK
This repository will host the tasks I completed with coding samurai during my C++ internship

I completed task 2, a tic-tac-toe game with two players, and you can restart the game. I implemented this by using OpenGL libraries to help me create an easy and user-friendly UI for the players.

I started by declaring 4 main variables
```cpp
int playerturn; // if it is 1, then it's the first player's turn. if it is 2, then it's the second player's turn
int matrix[3][3]; // Grid represented in a 2D matrix
int result; // if it is 0, then it's a draw; if it is 1, then Player X wins; if it is 2, then Player O wins
bool game over; // if it is false, then it's not game over. if it is true, then it's game over
```

Then I divided my code into groups of functions.
the first function being the initialization function.
```cpp
void initgame(){
    playerturn = 1; // X starts first
    // Clear the matrix
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            matrix[i][j] = 0;
        }
    }
}
```
which gives an initial value to the variables at the start of each new game.
it starts with player x's turn and all the cells in the grids are initialized with 0 (empty spaces)

function that draws the symbol x
```cpp
void drawX(float centerX, float centerY, float size) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red

    glBegin(GL_LINES);
    glVertex2f(centerX - size, centerY - size);
    glVertex2f(centerX + size, centerY + size);
    glVertex2f(centerX - size, centerY + size);
    glVertex2f(centerX + size, centerY - size);
    glEnd();
}
```

function that draws the symbol o
```cpp
void drawO(float centerX, float centerY, float radius) {
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green

    int numSegments = 100; // Increase this value for a smoother circle

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}
```

keyboard pressed function
```cpp
void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
        if (gameOver == true)
        {
            gameOver = false;
            initgame();
        }
        break;
    case 27:
        exit(0);
    }
}
```
this function handles when the letter 'r' is pressed on the keyboard it will reinitialize the game and start a new game
and escapes or exits the program when the exit key is pressed.

mouse clicked function
```cpp
void mouseClick(int button, int state, int x, int y)
{
    if (gameOver == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (matrix[(y - 50) / 100][x / 100] == 0)
        {
            if (playerturn == 1)
            {
                matrix[(y - 50) / 100][x / 100] = 1;
                playerturn = 2;
            }
            else
            {
                matrix[(y - 50) / 100][x / 100] = 2;
                playerturn = 1;
            }
        } 
    }
}
```
this function works by returning the position of the mouse clicked and using the equation (y-50)100 you can determine which cell on the y plane was clicked on as the function will return 0,1 or 2
same thing for x's equation x/100 to determine which cell on the x plane was clicked on. it also returns 0,1 or 2
after each cell is updates the player turn toggles to the other player.

function to display strings
```cpp
void drawString(void* font, string s, float x, float y) {
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < s.length(); i++)
        glutBitmapCharacter(font, s[i]);
}
```

function that draws the 3x3 grid by drawing 2 vertical lines and 2 horizontal lines
```cpp
void drawGrid() { 
    glLineWidth(2.0f); // Set line width to 2.0 units

    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f); //grey lines

    glVertex2f(100, 50);
    glVertex2f(100, 340);
    glVertex2f(200, 340);
    glVertex2f(200, 50);

    glVertex2f(0, 150);
    glVertex2f(300, 150);
    glVertex2f(0, 250);
    glVertex2f(300, 250);
    glEnd();
}
```

function to scan through the grid and draw the symbols according to the value stored in that cell
```cpp
void drawXO(){
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (matrix[i][j] == 1) // If it is 1, draw X
            {
                drawX(50 + j * 100, 100 + i * 100, 25);
            }
            else if (matrix[i][j] == 2) // If it is 2, draw O
            {
                drawO(50 + j * 100, 100 + i * 100, 25.0f);
            }
        }
    }
}
```
if the value is 0 it does nothing
if the value is 1 it draws x
if the value is 2 it draws y

function that checks the win condition
```cpp
bool checkIfWin(){
    // horizontal wins
    for (int i = 0; i < 3; i++) {
        if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2] && matrix[i][0] != 0) {
            return true;
        }
    }

    // vertical wins
    for (int i = 0; i < 3; i++) {
        if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i] && matrix[0][i] != 0) {
            return true;
        }
    }

    // diagonal wins
    if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[0][0] != 0) {
        return true;
    }

    // Check secondary diagonal
    if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[0][2] != 0) {
        return true;
    }

    return false;
}
```
this function checks if any of the win conditions are met
if 3 consecutive similar symbols are aligned horizontally, vertically or diagonally

function that checks the draw condition
```cpp
bool checkIfDraw() {
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
```
it works by checking if all the slots are taken (the grid doesn't have 0 values) and the win condition isn't met then it's a draw

function to display on the UI
```cpp
void display(){ // display objects

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    if (playerturn == 1)
        drawString(GLUT_BITMAP_HELVETICA_18, "Player X's turn", 100, 30);
    else
        drawString(GLUT_BITMAP_HELVETICA_18, "Player O's turn", 100, 30);

    drawGrid();
    drawXO();

    if (checkIfWin() == true)
    {
        if (playerturn == 1) // If Player O was the last one to play
        {
            gameOver = true;
            result = 2;
        }
        else // If Player X was the last one to play
        {
            gameOver = true;
            result = 1;
        }
    }
    else if (checkIfDraw() == true)
    {
        gameOver = true;
        result = 0;
    }

    if (gameOver == true)
    {
        glColor3f(1.0f, 1.0f, 1.0f); // white
        glRectf(20, 140, 280, 240);

        glColor3f(0.0f, 0.0f, 0.0f); // black
        drawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);

		if (result == 0)
			drawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);

		if (result == 1)
			drawString(GLUT_BITMAP_HELVETICA_18, "Player X wins", 95, 185);

		if (result == 2)
			drawString(GLUT_BITMAP_HELVETICA_18, "Player O wins", 95, 185);

		drawString(GLUT_BITMAP_HELVETICA_18, "Would you like to play again?", 40, 210);
		drawString(GLUT_BITMAP_HELVETICA_18, "(press r)", 110, 230);
	}

	glutSwapBuffers();
}
```
this function starts by displaying the player's turn according to who's turn is it (x or o)
then it draws the empty 3x3 grid
then it calls the drawXO() function to check the value of each cell and replace it with an x or o
after the win condition has been met it checks if player x or o won so the game can later display the winner
if the win condition hasn't been met the game displays a draw
when the game is over it displays the pop-up message "game over" and the player who won the game, or if it's a draw
then it would ask the players if they would like to play again and start a new game by pressing 'r' on their keyboard.

reshape function
```cpp
void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
```
The reshape function is called when the window is resized in an OpenGL application. It updates the viewport to match the new window dimensions, sets the projection matrix to an orthographic projection, and switches the matrix mode to the model-view matrix for transforming object coordinates.

main function
```cpp
int main(int argc, char** argv)
{
	initgame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(300, 350);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutMouseFunc(mouseClick);
	glutIdleFunc(display);
	glutMainLoop();
}
```
in this function it calls the initgame() function to initialize the game
then it setups some glut attributes for the UI like window size and position and display mode
it names the window "Tic Tac Toe"
it calls the reshape and display function I previously defined
it also calls the keyPressed and mouseClicked functions I previously defined
glutMainLoop() is called to keep the code running in a loop
