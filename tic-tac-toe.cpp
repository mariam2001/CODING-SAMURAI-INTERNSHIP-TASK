#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <glut.h>
#include <string>

using namespace std;

    // constants
int playerturn; // if it is 1, then it's the first player's turn. if it is 2, then it's the second player's turn
int matrix[3][3]; // Grid represented in a 2D matrix
int result; // if it is 0, then it's a draw; if it is 1, then Player X wins; if it is 2, then Player O wins
bool gameOver; // if it is false, then it's not game over. if it is true, then it's game over

    // functions

// Initialize the game
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

void drawX(float centerX, float centerY, float size) { //funcion that draws x
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red

    glBegin(GL_LINES);
    glVertex2f(centerX - size, centerY - size);
    glVertex2f(centerX + size, centerY + size);
    glVertex2f(centerX - size, centerY + size);
    glVertex2f(centerX + size, centerY - size);
    glEnd();
}

void drawO(float centerX, float centerY, float radius) { //function that draws o
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

// This function is called when a keyboard button is pressed
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

// This function is called when the mouse button is pressed and puts X or O on the blank box
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

void drawString(void* font, string s, float x, float y) { // To draw strings
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < s.length(); i++)
        glutBitmapCharacter(font, s[i]);
}

// Draw initial grid
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

// This function draws the X and O symbols
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

// This function checks if there is any winner
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


bool checkIfDraw() { // checks if all slots are taken
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

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

//This function is called on windows resize
void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

//main function of the program
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