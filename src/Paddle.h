#ifndef PADDLE_H_
#define PADDLE_H_

#include <FL/Fl_Box.H>
#include "Block.h"

class Paddle : public Block{
private:
	int num_blocks;

public:
	Paddle(int x, int y) : Block(x, y, 100, 20, FL_PLASTIC_UP_BOX, FL_BLUE){
		this->num_blocks = 5;
	}
};

#endif /* PADDLE_H_ */
