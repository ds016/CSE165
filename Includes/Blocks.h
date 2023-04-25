#ifndef BLOCKS_H
#define BLOCKS_H

class genBlock{ //generic block object to be inherited by the different versions
private:
	int health;
	float heightblock = 0.06f;
	float widthblock = 0.18f;
	float xblock, yblock;
public:

};

class yBlock:public genBlock{

};

class oBlock:public genBlock{

};

class rBlock:public genBlock{

};

#endif