#ifndef BRICK_H_
#define BRICK_H_

#include "Block.h"

class Brick : public Block{
private:
	int hitPoints;

public:
	Brick(int x, int y, Fl_Boxtype blockType, Fl_Color color, int hitPoints) : Block(x, y, blockType, color){
		this->hitPoints = hitPoints;
	}
};




#endif
