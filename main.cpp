#define _USE_MATH_DEFINES
#include <cmath>
#include <GLFW/glfw3.h>
#include "Ball.h"
#include "Blocks.h"
#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;

// game window dimension and class declaration
int widthwindow = 720;
int heightwindow = 720;
Player player;
Ball ball;


void drawBlocks() {
    // define the brick dimensions
    float widthblock = 0.055f;
    float heightblock = 0.01f;
    
    // offset during the creation so blocks are not
    float gap = 0.07f;
     
    // formation of the bricks
    int row = 7;
    int col = 16;
    
    // Creating a standalone "health block" check
    bool blocks[row][col];
    
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // **** Change if needed ****
            blocks[row][col] = true;
            
            if (blocks[row][col]) {
                // we are assuming a uniform coordinate system of [-1.0f, 1.0f]
                float xblock = -0.99 + widthblock + (j * (widthblock + gap));
                float yblock = 0.8 - heightblock - (i * (heightblock + gap));
                
                // set the color to red as a test
                glColor3f(1.0, 0.0, 0.0);
                
                // for loop that will DRAW the block
                glBegin(GL_QUADS);
                
                // bot left -> bot right -> top right -> top left
                glVertex2f(xblock - widthblock, yblock - heightblock);
                glVertex2f(xblock + widthblock, yblock - heightblock);
                glVertex2f(xblock + widthblock, yblock + heightblock);
                glVertex2f(xblock - widthblock, yblock + heightblock);
                
                // end drawing process
                glEnd();
                
                if ( (xball + radiusball > xblock - widthblock) &&
                    (xball - radiusball < xblock - widthblock) &&
                    (yball + radiusball > yblock - widthblock) &&
                    (yball - radiusball < yblock + widthblock))  {
                    
                    if((xball > xblock - widthblock) &&
                       (xball < xblock + widthblock)) {
                        
                        yvelocityball = -1 * yvelocityball;
                    }
                    
                    if((yball > yblock + heightblock) &&
                       (yball < yblock + heightblock)) {
                        
                        xvelocityball = -1 * xvelocityball;
                    }
                    
                    blocks[row][col] = false;
                }
            }
            
        } // end J loop
    }   // end I loop
}



// function to handle mouse input for the movement of player
void mousefunc(GLFWwindow* window, double xcord, double ycord)
{

    // Determining the mouse position & converting that into the relative position on the application window
    float xposition = (float)xcord / (float)widthwindow * 2.0f - 1.0f;
    
    // The coordinate plane is using normal coordinate values... min = -1, max = 1 on the x and y axis
    float leftx = 0.9f;
    float rightx = -0.9f;

    // Checking if player model ever hits bounds, if bound is hit, condition. If not, player matches cursor
    if (xposition > leftx) {
        player.setxpaddle(leftx);
    }
    else if (xposition < rightx) {
        player.setxpaddle(rightx);
    }
    else {
        player.setxpaddle(xposition);
    }

}
    
int main() {
    // create the window instance here
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(widthwindow, heightwindow, "Atari Breakout Progression", NULL, NULL);
    if (!window)
    {
        cerr << "Error: Could not create the window"  << endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Position the cursor before creating the drawing */
    glfwSetCursorPosCallback(window, mousefunc);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        

        // clear the screen before drawing
        glClear(GL_COLOR_BUFFER_BIT);

        // create the player model in the window context
        player.createPaddle();

        // create the ball model in the window context
        ball.createBall();

        // create the movement of the ball
        ball.ballmovement(player);

        // Spawn the blocks
        drawBlocks();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    
    }

    glfwTerminate();
    return 0;
}
