#ifndef BLOCKS_H
#define BLOCKS_H

#include <GLFW/glfw3.h>
#include <iostream>

class genBlock { //generic block object to be inherited by the different versions
private:
	int health;
	bool alive;
	float heightblock = 0.06f;
	float widthblock = 0.18f;
	float xblock, yblock;
public:
	genBlock() {}
	~genBlock() {}

	float getxblock() { return xblock; }
	float getyblock() { return yblock; }
	void setxblock(float xcoord) {}
	void setyblock(float ycoord) {}

	virtual int losehealth() {}

	void blockhit() {
		if (alive == true) 
			if (health-- == 0) 
				alive = false;
	}

};

class yBlock:public genBlock{
private:
	int health = 1;
public:
	yBlock(float xcoord, float ycoord) {
		setxblock(xcoord);
		setyblock(ycoord);
		alive = true;
	}
	float getxblock() { return this->xblock; }
	float getyblock() { return this->yblock; }

	
};

class oBlock:public genBlock{
private:
	int health = 2;
public:
	oBlock(float xcoord, float ycoord) {
		this->xblock = xcoord;
		this->yblock = ycoord;
		alive = true;
	}
	float getxblock() { return this->xblock; }
	float getyblock() { return this->yblock; }
};

class rBlock:public genBlock{
private:
	int health = 3;
public:
	rBlock(float xcoord, float ycoord) {
		this->xblock = xcoord;
		this->yblock = ycoord;
		alive = true;
	}
	float getxblock() { return this->xblock; }
	float getyblock() { return this->yblock; }
};

#endif