#ifndef PADDLE_H_
#define PADDLE_H_

#include <FL/Fl_Box.H>

class Paddle : public Fl_Box{
private:
	int num_blocks;

public:
	Paddle(int x, int y) : Fl_Box(x, y, 100, 20){
		this->num_blocks = 5;
	}
};

#endif /* PADDLE_H_ */
