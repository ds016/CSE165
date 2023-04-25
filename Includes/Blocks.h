#ifndef BLOCKS_H
#define BLOCKS_H

class genBlock{ //generic block object to be inherited by the different versions
private:
	int health;
	bool alive;
	float heightblock = 0.06f;
	float widthblock = 0.18f;
	float xblock, yblock;
public:
	virtual genBlock() {}
	virtual ~genBlock() {}

	virtual float getxblock() {}
	virtual float getyblock() {}
	virtual void setxblock() {}
	virtual void setyblock() {}

	virtual int losehealth() {}

	void blockhit() {
		if (alive == true) 
			if (health-- == 0) 
				alive = false;
	}

};

class yBlock:public genBlock{
private:
	health = 1;
public:
	yBlock(float xcoord, float ycoord) {
		this->xblock = xcoord;
		this->yblock = ycoord;
		alive = true;
	}
	float getxblock() { return this->xblock; }
	float getyblock() { return this->yblock; }

	
};

class oBlock:public genBlock{
private:
	health = 2;
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
	health = 3;
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