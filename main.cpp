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


    // set the rectangle to the color white 
    glColor3f(0.0f, 0.0f, 1.0f);

    // Drawing process 
    glBegin(GL_QUADS);

    glVertex2f(xpaddle, ypaddle);
    glVertex2f(xpaddle + widthpaddle, ypaddle);
    glVertex2f(xpaddle + widthpaddle, ypaddle + heightpaddle);
    glVertex2f(xpaddle, ypaddle + heightpaddle);

    glEnd();

}

    
int main(void) {   
    // create the window instance here
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(widthwindow, heightwindow, "Hello World", NULL, NULL);
    if (!window)
    {
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
