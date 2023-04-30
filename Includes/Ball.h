#ifndef BALL_H
#define BALL_H

#include <GLFW/glfw3.h>
#include <Player.h>
#include <iostream>
#include <math.h>


class Ball {
private:
    // radius of ball
    float radiusball = 0.02f;

    // ball initial position spawn
    float xball = 0.0f;
    float yball = -0.5f;

    // to create movement, there needs to be velocity values [INITIAL VELOCITY]
    float xvelocityball = 0.001f;
    float yvelocityball = -0.005f;

public:
    float getradiusball() { return radiusball; }
    float getxball() { return xball; }
    float getyball() { return yball; }
    void setxball(float extra) { xball += extra; }
    void setyball(float extra) { yball += extra; }
    float getxvelocityball() { return xvelocityball; }
    float getyvelocityball() { return yvelocityball; }
    void setxvelocityball(float newv) { xvelocityball = newv; std::cout << "x: " << newv << std::endl; }
    void setyvelocityball(float newv) { yvelocityball = newv; std::cout << "y: " << newv << std::endl;}

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
            angle = i * 2.0f * M_PI / 100;
            // using sin/cos functions to determine the position multiplied by radius for sizing and add to x position for each triangle to draw a part of ball
            glVertex2f(xball + cos(angle) * radiusball, yball + sin(angle) * radiusball);
        }

        glEnd();

    }

    void ballmovement(Player& player) {
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

};

#endif