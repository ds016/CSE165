#ifndef PLAYER_H
#define PLAYER_H

#include <GLFW/glfw3.h>
#include <iostream>

class Player
{
private:
    // paddle's dimension
    float widthpaddle = 0.2f;
    float heightpaddle = 0.02f;

    // paddle initial position spawn
    float xpaddle = 0.0f;
    float ypaddle = -0.95f;

public:
    //getter/setter
    float getxpaddle()
    {
        return xpaddle;
    }

    float getypaddle()
    {
        return ypaddle;
    }

    float getwidthpaddle()
    {
        return widthpaddle;
    }

    float getheightpaddle()
    {
        return heightpaddle;
    }

    void setxpaddle(float x)
    {
        this->xpaddle = x;
    }

    void setypaddle(float y)
    {
        this->ypaddle = y;
    }

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

};

#endif