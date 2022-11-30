#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <FL/Fl_Box.H>

class Paddle : public Fl_Box{
private:
	//ADD THREE INVISIBLE BLOCKS
	//FRONT 20% IS ONE BLOCK, BACK 20% IS ONE BLOCK, MIDDLE IS ONE BLOCK
	//BALL BOUNCE NORMAL ON MIDDLE, BOUNCE DIFFERENT ON FRONT AND BACK
	int width = 120; // 5 blocks of 20x24 or 3 blocks, 1 x (72x20) + 2 x (24x20)
	int height = 20;
	int max_x = 640;
	int min_x = 0;
	int speed = 10;
	int direction = 0;

public:
	Paddle(int x, int y, int width, int height) : Fl_Box(x, y, width, height){
		this->box(FL_UP_BOX);
		this->color(FL_WHITE);
	}

	void move();
	void moveLeft();
	void moveRight();

};

void Paddle::moveLeft(){
	direction = -1;
	this->move();
}

void Paddle::moveRight(){
	direction = 1;
	this->move();
}



void Paddle::move(){
	this->hide();
	int new_x = this->x() + this->direction * this->speed;
	if(new_x >= this->max_x - this->w()){
		new_x = this->max_x - this->w();
	}
	else if (new_x <= this->min_x){
		new_x = this->min_x;
	}
	else{
		new_x = this->x() + this->speed * this->direction;
	}
	this->position(new_x, 460);
	this->show();
	direction = 0;
}

#endif /* _PADDLE_H_ */
