#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;


// window dimension
int widthwindow = 640;
int heightwindow = 480;

// paddle dimension
int widthpaddle = 100;
int heightpaddle = 20;

// paddle initial position spawn
float xpaddle = (widthwindow - widthpaddle / 2.0f);
float ypaddle = (heightwindow - heightpaddle / 10.0f);



// function to create the paddle
void createPaddle() {

    // Drawing process 
    glBegin(GL_QUADS);

    // set the rectangle to the color red 
    glColor3f(1.0f, 0.0f, 0.0f);

    // ********** IMPORTANT, WHEN CREATING SHAPES, MUST DRAW CCW, BOT-LEFT -> BOT-RIGHT -> TOP-RIGHT -> TOP-LEFT; **************

    // Example code to create a red paddle in the middle of the window screen 
    glVertex2f(-0.8, -0.1);
    glVertex2f(0.8, -0.1);

    glVertex2f(0.8, 0.1);
    glVertex2f(-0.8, 0.1);

    glEnd();

}

void errorCatch(int error, const char* description) {
    cerr << "Error: " << description << endl;
}

    
int main() {   
    // create the window instance here
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwSetErrorCallback(errorCatch);
    
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {   
        

        // clear the screen before drawing
        glClear(GL_COLOR_BUFFER_BIT);

        // create the rectangle in the window context
        createPaddle();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}
