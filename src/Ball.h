#ifndef BALL_H_
#define BALL_H_

#include <FL/Fl_Box.H>

class Ball : public Fl_Box{
private:
	int xSpeed;
	int ySpeed;
public:
	void setSpeed(int xSpd, int ySpd);

	void move();

	//if ball hits object in x direction
	void bounceHorizontal();

	//if ball hits object in y direction
	void bounceVertical();

	Ball(int x, int y): Fl_Box(x, y, 15, 15){
		this->xSpeed = 0;
		this->ySpeed = 0;
		this->box(FL_OVAL_BOX);
		this->color(FL_RED);
	}

};


//Function definitions

void Ball::setSpeed(int xSpd, int ySpd){
	this->xSpeed = xSpd;
	this->ySpeed = ySpd;
}

void Ball::move(){
	//NEED TO CHECK FOR COLLISION IF MOVED ------------------------------------
	this->hide();
	int new_x;
	int new_y;
	new_x = this->x() + this->xSpeed;
	new_y = this->y() + this->ySpeed;
	this->position(new_x, new_y);
	this->show();
}

void Ball::bounceHorizontal(){
	this->xSpeed = -(xSpeed);
}

void Ball::bounceVertical(){
	this->xSpeed = -(xSpeed);
}


#endif /* BALL_H_ */
