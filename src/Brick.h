#ifndef BRICK_H_
#define BRICK_H_

#include "Block.h"

class Brick : public Block{
private:
	int hitPoints;

public:
	Brick(int x, int y, int hitPoints) : Block(x, y, 20, 20, FL_THIN_UP_BOX, FL_YELLOW){
		this->hitPoints = hitPoints;
		this->labelfont(1);
		if (hitPoints == 3){
			this->label("3");
		}
	}
};




#endif
