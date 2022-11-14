#ifndef PADDLE_H_
#define PADDLE_H_

#include <FL/Fl_Box.H>
#include "Block.h"

class Paddle : public Block{
private:
	//ADD THREE INVISIBLE BLOCKS
	//FRONT 20% IS ONE BLOCK, BACK 20% IS ONE BLOCK, MIDDLE IS ONE BLOCK
	//BALL BOUNCE NORMAL ON MIDDLE, BOUNCE DIFFERENT ON FRONT AND BACK

public:
	Paddle(int x, int y) : Block(x, y, 100, 20, FL_PLASTIC_UP_BOX, FL_BLUE){

	}
};

#endif /* PADDLE_H_ */
