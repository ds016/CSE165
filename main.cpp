#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;


// game window dimension
int widthwindow = 1000;
int heightwindow = 1000;

// paddle's dimension
float widthpaddle = 0.2f;
float heightpaddle = 0.02f;

// paddle initial position spawn
float xpaddle = 0.0f;
float ypaddle = -0.95f;


// function to create the paddle
void createPaddle() {

    // Drawing process   
    glBegin(GL_QUADS);

    // set the rectangle to the color red 
    glColor3f(1.0f, 0.0f, 0.0f);

    // ********** IMPORTANT, WHEN CREATING SHAPES, MUST DRAW CCW, BOT-LEFT -> BOT-RIGHT -> TOP-RIGHT -> TOP-LEFT; **************

    // Example code to create a red paddle in the middle of the window screen 
    glVertex2f(xpaddle - (widthpaddle / 2), ypaddle);      // Bottom Left vertice
    glVertex2f(xpaddle + (widthpaddle / 2), ypaddle);      // Bottom Right vertice 

    glVertex2f(xpaddle + (widthpaddle / 2), ypaddle + heightpaddle);   // Top Right Vertice
    glVertex2f(xpaddle - (widthpaddle / 2), ypaddle + heightpaddle);   // Top Left Vertice

    // End drawing operation
    glEnd();       
}


void mousefunc(GLFWwindow* window, double xcord, double ycord) {

    // Determining the mouse position & converting that into the relative position on the application window
    float xposition = (float)xcord / (float)widthwindow * 2.0f - 1.0f;
    xpaddle = xposition;

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
        createPaddle();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    
    }

    glfwTerminate();
    return 0;
}
