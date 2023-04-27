#include <GLFW/glfw3.h>
#include <Ball.h>
#include <Blocks.h>
#include <Player.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// const variable
const float PI = 3.14159265358979323f;

// game window dimension
int widthwindow = 720;
int heightwindow = 720;
Player player;

// radius of ball
float radiusball = 0.02f;

// ball initial position spawn
float xball = 0.0f; 
float yball = 0.0f;

// to create movement, there needs to be velocity values [INITIAL VELOCITY]
float xvelocityball = 0.001f;
float yvelocityball = -0.01f;

// function to draw the ball model
void createBall() {
    // Drawing process 
    glBegin(GL_TRIANGLE_FAN);

    // Set the color of ball model to red 
    glColor3f(1.0f, 0.0f, 0.0f);

    // Set center of the ball 
    glVertex2f(xball, yball);

    float angle; 

    // Increasing the loop end condition will result in a better drawn circle, uses triangles to create a circle shape, more triangle = more accurate circle
    for (int i = 0; i < 10000; i++) {
        // calculates the angle from each of the triangles being drawn (2PI is full circle)
        angle = i * 2.0f * PI / 100;
        // using sin/cos functions to determine the position multiplied by radius for sizing and add to x position for each triangle to draw a part of ball
        glVertex2f(xball + cos(angle) * radiusball, yball + sin(angle) * radiusball);
    }

    glEnd();

}

// function to handle mouse input for the movement of player
void mousefunc(GLFWwindow* window, double xcord, double ycord) {

    // Determining the mouse position & converting that into the relative position on the application window
    float xposition = (float)xcord / (float)widthwindow * 2.0f - 1.0f;
    
    // The coordinate plane is using normal coordinate values... min = -1, max = 1 on the x and y axis
    float leftx = 0.9;
    float rightx = -0.9;

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

void ballmovement() {
    // The coordinate plane is using normal coordinate values... min = -1, max = 1 on the x and y axis
    float leftx = -1.0;
    float rightx = 1.0;

    // top and bottom bound 
    float topy = 1.0;
    float boty = -1.0;


    // updating the ball's position with velocity values, AKA "shifting the position by velocity values
    xball += xvelocityball;
    yball += yvelocityball;

    if (xball > rightx) {
        xvelocityball = -1 * (xvelocityball);
    }

    if (xball < leftx) {
        xvelocityball = -1 * (xvelocityball);
    }

    if (yball > topy) {
        yvelocityball = -1 * (yvelocityball);
    }

    // need to return game over if this is going to be the end (FINISH THIS LATER)
    if (yball < boty) {
        yvelocityball = -1 * (yvelocityball);
    }


    // --> check if yball is less than / equal to top of paddle (height)
    // --> check if xball is within bounds of widthpaddle (width)
    //      --> change yballvelocity to negative

    if (yball - radiusball < player.getypaddle() + player.getheightpaddle() 
        && yball > player.getypaddle() 
        && xball + radiusball > player.getxpaddle() - player.getwidthpaddle() 
        && xball - radiusball < player.getxpaddle() + player.getwidthpaddle()) {
        // yball = ypaddle + heightpaddle / 2 + radiusball;
        yvelocityball = -1 * yvelocityball;
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
        createBall();

        // create the movement of the ball
        ballmovement();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    
    }

    glfwTerminate();
    return 0;
}
