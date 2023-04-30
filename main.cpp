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
std::vector<genBlock*> Grid = generateBlocks();

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
        cerr << "Error: Could not create the window" << endl;
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
        
        // Spawn the blocks
        createBlocks(Grid,ball);
        
        // create the movement of the ball
        ball.ballmovement(player);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}
