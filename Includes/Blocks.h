#ifndef BLOCKS_H
#define BLOCKS_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

const float height = 0.1f;
const float width = (float)(1/7);


class genBlock {	//generic block object to be inherited by the different versions
private:
	bool alive=false;	//bool status for life of block, used to display
	int health=0;	//keeps track of times it's been hit, to be used for color
	float xblock, yblock=0.0f;	//coords of block, bottom left corner
public:
	virtual float getxblock() { return xblock; }
	virtual float getyblock() { return yblock; }
	virtual void setxblock(float xcoord) { xblock = xcoord; }
	virtual void setyblock(float ycoord) { yblock = ycoord; }

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
	}
};


std::vector<genBlock*> generateBlocks() {//14wide,9tall; flush to top and side; height=.1, width=1/7
	std::vector<genBlock*> grid;	//stored top->bottom, left->right
	
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 14; x++) {
			if (y < 3) {
				grid.push_back(new rBlock(-1 + (width * x), 1 - (height * (y + 1))));
			}
			else if (3 <= y && y < 6) {
				grid.push_back(new oBlock(-1 + (width * x), 1 - (height * (y + 1))));
			}
			else{
				grid.push_back(new yBlock(-1 + (width * x), 1 - (height * (y + 1))));
			}
		}
	}

	return grid;
}


#endif