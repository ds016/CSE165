#ifndef BLOCKS_H
#define BLOCKS_H

#include <GLFW/glfw3.h>
#include <Ball.h>
#include <iostream>
#include <vector>

const int basehealth = 1;
const float height = 0.01f;
const float width = 0.055f;
const float gap = 0.07f;
extern int gamehealth;

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

class yBlock :public genBlock {
private:
	bool alive;
	int health;
	float xblock, yblock;
public:
	yBlock(float xcoord, float ycoord) {
		setxblock(xcoord);
		setyblock(ycoord);
		health = basehealth;
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
			if (health > 1) {
				health--;
				
			}
			else {
				alive = false;
				gamehealth--;
			}
				
		}
		std::cout << "yellow hit " << std::endl;
	}
};

class oBlock :public genBlock {
private:
	bool alive;
	int health;
	float xblock, yblock;
public:
	oBlock(float xcoord, float ycoord) {
		this->xblock = (xcoord);
		this->yblock = (ycoord);
		health = 2 * basehealth;
		alive = true;
	}
	bool getlive() { return alive; };
	int gethealth() { return health; }
	float getxblock() { return xblock; }
	float getyblock() { return yblock; }
	void setxblock(float xcoord) { xblock = xcoord; }
	void setyblock(float ycoord) { yblock = ycoord; }

	void blockhit() {
		/*if (health > 1) {
			health--;
			reinterpret_cast<yBlock*>(this);
		}
		std::cout << "orange hit" << std::endl;*/
		if (alive == true) {
			if (health > 1) {
				health--;
			}
			else {
				alive = false;
				gamehealth--;
			}
		}
		std::cout << "orange hit" << std::endl;
	}
};

class rBlock :public genBlock {
private:
	bool alive;
	int health;
	float xblock, yblock;
public:
	rBlock(float xcoord, float ycoord) {
		this->xblock = xcoord;
		this->yblock = ycoord;
		health = 3 * basehealth;
		alive = true;
	}
	bool getlive() { return alive; };
	int gethealth() { return health; }
	float getxblock() { return xblock; }
	float getyblock() { return yblock; }
	void setxblock(float xcoord) { xblock = xcoord; }
	void setyblock(float ycoord) { yblock = ycoord; }

	void blockhit() {
		/*if (health > 2) {
			health--;
			reinterpret_cast<oBlock*>(this);
		}
		alive = false;
		std::cout << "red hit" << std::endl;
		return oBlock(this);*/
		if (alive == true) {
			if (health > 1) {
				health--;
			}
			else {
				alive = false;
				gamehealth--;
			}
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
			else {
				grid.push_back(new yBlock(-0.99 + width + (x * (width + gap)), 0.8 - height - (y * (height + gap))));
			}
		}
	}
	return grid;
}

void collisioncheck(genBlock* block, Ball& ball) {		//ball and block collision checking
	float leftBallbound = ball.getxball() - ball.getradiusball();
	float rightBallbound = ball.getxball() + ball.getradiusball();;
	float bottomBallbound = ball.getyball() - ball.getradiusball();;
	float topBallbound = ball.getyball() + ball.getradiusball();;

	float leftBlockbound = block->getxblock() - gap;
	float rightBlockbound = block->getxblock() + (width);
	float bottomBlockbound = block->getyblock();
	float topBlockbound = block->getyblock() + (height);

	if (leftBallbound < rightBlockbound &&
		rightBallbound > leftBlockbound &&
		topBallbound > bottomBlockbound &&
		bottomBallbound < topBlockbound) {

		block->blockhit();
		ball.setyvelocityball(-1 * ball.getyvelocityball());
		if (ball.getxvelocityball() > 0)
			ball.setxvelocityball((rand() % 5) * 0.0005f);
		else ball.setxvelocityball(-1 * (rand() % 5 + 1) * 0.0005f);

		ball.setxballforce(ball.getxvelocityball());
		ball.setyballforce(ball.getyvelocityball());

	}
}

void createBlocks(std::vector<genBlock*> grid, Ball& ball) {
	for (int i = 0; i < grid.size(); i++) {
		if (grid[i]->getlive()) {
			if (grid[i]->gethealth() > 2 * basehealth) {
				// set the rectangle to the color red 
				glColor3f(1.0f, 0.0f, 0.0f);
				// Drawing process   
				glBegin(GL_QUADS);

				// Example code to create a red paddle in the middle of the window screen 
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() - height);      // Bottom Left vertice
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() - height);      // Bottom Right vertice 
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() + height);   // Top Right Vertice
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() + height);   // Top Left Vertice

				// End drawing operation
				glEnd();
				collisioncheck(grid[i], ball);
			}
			else if (grid[i]->gethealth() > basehealth) {
				// set the rectangle to the color orrange 
				glColor3f(1.0f, 0.5f, 0.0f);
				// Drawing process   
				glBegin(GL_QUADS);

				// Example code to create a red paddle in the middle of the window screen 
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() - height);   // Bottom Left vertice
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() - height);   // Bottom Right vertice 
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
				glVertex2f(grid[i]->getxblock() - width, grid[i]->getyblock() - height);   // Bottom Left vertice
				glVertex2f(grid[i]->getxblock() + width, grid[i]->getyblock() - height);   // Bottom Right vertice 
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