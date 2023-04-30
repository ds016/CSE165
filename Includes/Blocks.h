#ifndef BLOCKS_H
#define BLOCKS_H

#include <GLFW/glfw3.h>
#include <Ball.h>
#include <iostream>
#include <vector>

const float height = 0.01f;
const float width = 0.055f;
const float gap = 0.07f;


class genBlock {	//generic block object to be inherited by the different versions
private:
	bool alive = false;	//bool status for life of block, used to display
	int health = 0;	//keeps track of times it's been hit, to be used for color
	float xblock = 0.0f;
	float yblock = 0.0f;	//coords of block, bottom left corner
public:
	virtual bool getlive() { return alive; };
	int virtual gethealth() { return health; }
	virtual float getxblock() { return xblock; }
	virtual float getyblock() { return yblock; }
	virtual void setxblock(float xcoord) { xblock = xcoord; }
	virtual void setyblock(float ycoord) { yblock = ycoord; }
	float getwidth() { return width; }
	float getheight() { return height; }

	virtual void blockhit() = 0;	//pure virtual function to make this abstract, 
									//the point of it is to deal with modifying block data once hit
};

class yBlock:public genBlock{
private:
	bool alive;
	int health = 1;
	float xblock, yblock;
public:
	yBlock(float xcoord, float ycoord) {
		setxblock(xcoord);
		setyblock(ycoord);
		alive = true;
	}
	bool getlive() { return alive; };
	int gethealth() { return health; }
	float getxblock() { return xblock; }
	float getyblock() { return yblock; }
	void setxblock(float xcoord) { xblock = xcoord; }
	void setyblock(float ycoord) { yblock = ycoord; }

	void blockhit() {
		if (alive == true) {
			if (health > 0) {
				health--;
				alive = false;
			}
		}
		std::cout << "yellow hit" << std::endl;
	}
};

class oBlock:public genBlock{
private:
	bool alive;
	int health = 2;
	float xblock, yblock;
public:
	oBlock(float xcoord, float ycoord) {
		setxblock(xcoord);
		setyblock(ycoord);
		alive = true;
	}
	bool getlive() { return alive; };
	int gethealth() { return health; }
	float getxblock() { return xblock; }
	float getyblock() { return yblock; }
	void setxblock(float xcoord) { xblock = xcoord; }
	void setyblock(float ycoord) { yblock = ycoord; }

	void blockhit() {
		if (health > 1) {
			health--;
			dynamic_cast<yBlock*>(this);
		}
		std::cout << "orange hit" << std::endl;
	}
};

class rBlock:public genBlock{
private:
	bool alive;
	int health = 3;
	float xblock, yblock;
public:
	rBlock(float xcoord, float ycoord) {
		this->xblock = xcoord;
		this->yblock = ycoord;
		alive = true;
	}
	bool getlive() { return alive; };
	int gethealth() { return health; }
	float getxblock() { return xblock; }
	float getyblock() { return yblock; }
	void setxblock(float xcoord) { xblock = xcoord; }
	void setyblock(float ycoord) { yblock = ycoord; }

	void blockhit() {
		if (health > 2) {
			health--;
			dynamic_cast<oBlock*>(this);
		}
		std::cout << "red hit" << std::endl;
	}
};


std::vector<genBlock*> generateBlocks() {
	std::vector<genBlock*> grid;	//stored top->bottom, left->right
	
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 16; x++) {
			if (y < 3) {
				grid.push_back(new rBlock(-0.99 + width + (x * (width + gap)), 0.8 - height - (y * (height + gap))));
			}
			else if (3 <= y && y < 6) {
				grid.push_back(new oBlock(-0.99 + width + (x * (width + gap)), 0.8 - height - (y * (height + gap))));
			}
			else{
				grid.push_back(new yBlock(-0.99 + width + (x * (width + gap)), 0.8 - height - (y * (height + gap))));
			}
		}
	}

	return grid;
}

void collisioncheck(genBlock* block, Ball& ball) {		//ball and block collision checking
	if ((ball.getxball() + ball.getradiusball() > block->getxblock() - width) &&
		(ball.getxball() - ball.getradiusball() < block->getxblock() - width) &&
		(ball.getyball() + ball.getradiusball() > block->getyblock() - width) &&
		(ball.getyball() - ball.getradiusball() < block->getyblock() + width)) {

		if ((ball.getxball() > block->getxblock() - width) &&
			(ball.getxball() < block->getxblock() + width)) {

			ball.setyvelocityball(-1 * ball.getyvelocityball());
			block->blockhit();
		}
		else if ((ball.getyball() > block->getyblock() + height) &&
			(ball.getyball() < block->getyblock() + height)) {

			ball.setxvelocityball(-1 * ball.getxvelocityball());
			block->blockhit();
		}
	}
}

void createBlocks(std::vector<genBlock*> grid, Ball& ball) {
	
	for (int i = 0; i < grid.size(); i++) {
		if (grid[i]->getlive()) {
			if (grid[i]->gethealth() == 3) {
				// set the rectangle to the color red 
				glColor3f(1.0f, 0.0f, 0.0f);
				// Drawing process   
				glBegin(GL_QUADS);

				// Example code to create a red paddle in the middle of the window screen 
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock()-height);      // Bottom Left vertice
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock()-height);      // Bottom Right vertice 
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() + height);   // Top Right Vertice
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() + height);   // Top Left Vertice

				// End drawing operation
				glEnd();
				collisioncheck(grid[i], ball);
			}
			else if (grid[i]->gethealth() == 2) {
				// set the rectangle to the color orrange 
				glColor3f(1.0f, 0.5f, 0.0f);
				// Drawing process   
				glBegin(GL_QUADS);

				// Example code to create a red paddle in the middle of the window screen 
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock()-height);      // Bottom Left vertice
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock()-height);      // Bottom Right vertice 

				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() + height);   // Top Right Vertice
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() + height);   // Top Left Vertice

				// End drawing operation
				glEnd();
				collisioncheck(grid[i], ball);
			}
			else {
				// set the rectangle to the color yellow 
				glColor3f(1.0f, 1.0f, 0.0f);
				// Drawing process   
				glBegin(GL_QUADS);

				// Example code to create a red paddle in the middle of the window screen 
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock()-height);      // Bottom Left vertice
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock()-height);      // Bottom Right vertice 

				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() + height);   // Top Right Vertice
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() + height);   // Top Left Vertice

				// End drawing operation
				glEnd();
				collisioncheck(grid[i], ball);
			}
		}
	}
}

#endif