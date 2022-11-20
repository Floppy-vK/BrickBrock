#ifndef BALL_H_
#define BALL_H_

#include <FL/Fl_Box.H>
#include "Paddle.h"
#include "Bricks.h"
#include "Brick.h"
#include <vector>
using namespace std;

//structure to save coordinates
struct coord{
	int x;
	int y;
	char direction;
};

class Ball : public Fl_Box{
private:
	int min_x = 0;
	int max_x = 640;
	int min_y = 0;
	int max_y = 480;
	int xSpeed;
	int ySpeed;
	int diameter;

	bool isAlive = true;
	bool bouncedPaddle = false;

	vector<coord> cardinals;
	vector<coord> diagonals;


public:
	Ball(int x, int y, int diameter = 20): Fl_Box(x, y, diameter, diameter){
		this->diameter = diameter;
		this->xSpeed = 0;
		this->ySpeed = 0;
		this->box(FL_OVAL_BOX);
		this->color(FL_RED);
		this->cardinals.resize(4);
		this->diagonals.resize(4);
	}

	void setSpeed(int xSpd, int ySpd);

	bool move();

	//if ball hits object in x direction
	void bounceHorizontal();

	//if ball hits object in y direction
	void bounceVertical();

	//checks if the ball must bounce against walls
	void checkWallBounce();

	//sets new collision point locations
	void setNewCPoints();

	//checks for collision
	void checkCollision(Paddle *paddle, Bricks *bricks);

	//checks collision for coordinates given
	//void checkOverlap(coord);

	void bounceAngle(char name);
};


//Function definitions

void Ball::setSpeed(int xSpd, int ySpd){
	this->xSpeed = xSpd;
	this->ySpeed = ySpd;
}

bool Ball::move(){
	//NEED TO CHECK FOR COLLISION IF MOVED ------------------------------------
	this->hide();
	int new_x;
	int new_y;

	this->checkWallBounce();

	new_x = this->x() + this->xSpeed;
	new_y = this->y() + this->ySpeed;

	this->position(new_x, new_y);
	this->setNewCPoints();
	this->show();
	return this->isAlive;
}

void Ball::bounceHorizontal(){
	this->xSpeed = -(xSpeed);
}

void Ball::bounceVertical(){
	this->ySpeed = -(ySpeed);
}

void Ball::checkWallBounce(){
	if (this->x() >= this->max_x - this->diameter or this->x() <= this->min_x){
			this->bounceHorizontal();
	}
	if (this->y() <= this->min_y){
			this->bounceVertical();
	}
	if (this->y() >= this->max_y - this->diameter){
		this->isAlive = false;
	}
}

void Ball::setNewCPoints(){
	int margin = 1;
	//names are as the letters on keyboard centered around s key
	// q w e
	// a s d
	// z x c

	//cardinal point north
	this->cardinals.at(0).x = this->x() + this->diameter/2;
	this->cardinals.at(0).y = this->y() - margin;
	this->cardinals.at(0).direction = 'v';

	//cardinal point east
	this->cardinals.at(1).x = this->x() + this->diameter + margin;
	this->cardinals.at(1).y = this->y() + this->diameter/2;
	this->cardinals.at(1).direction = 'h';

	//cardinal point south
	this->cardinals.at(2).x = this->x() + this->diameter/2;
	this->cardinals.at(2).y = this->y() + this->diameter + margin;
	this->cardinals.at(2).direction = 'v';

	//cardinal point west
	this->cardinals.at(3).x = this->x() - margin;
	this->cardinals.at(3).y = this->y() + this->diameter/2;
	this->cardinals.at(3).direction = 'h';

	//diagonal point top-left
	this->diagonals.at(0).x = this->x() + 0.15*diameter - margin;
	this->diagonals.at(0).y = this->y() + 0.15*diameter - margin;
	this->diagonals.at(0).direction = 'd';

	//diagonal point top-right
	this->diagonals.at(1).x = this->x() + 0.85*diameter + margin;
	this->diagonals.at(1).y = this->y() + 0.15*diameter - margin;
	this->diagonals.at(1).direction = 'd';

	//diagonal point bottom-right
	this->diagonals.at(2).x = this->x() + 0.85*diameter + margin;
	this->diagonals.at(2).y = this->y() + 0.85*diameter + margin;
	this->diagonals.at(2).direction = 'd';

	//diagonal point bottom-left
	this->diagonals.at(3).x = this->x() + 0.15*diameter - margin;
	this->diagonals.at(3).y = this->y() + 0.85*diameter + margin;
	this->diagonals.at(3).direction = 'd';
}

void Ball::checkCollision(Paddle *paddle, Bricks *bricks){
	if (this->y() < 480 - paddle->h() - this->diameter){
		this->bouncedPaddle = false;
	}

	//paddle collision check
	if (not this->bouncedPaddle){
		for (coord c : this->cardinals){
			if (c.y >= paddle->y() and c.y <= paddle->y() + paddle->h()){
				if (c.x >= paddle->x() and c.x <= paddle->x() + paddle->w()){
					//check direction for bounce
					this->bounceAngle(c.direction);
					this->bouncedPaddle = true;
				}
			}
		}
	}

	if (not this->bouncedPaddle){
		for (coord c : this->diagonals){
			if (c.x >= paddle->x() and c.x <= paddle->x() + paddle->w()){
				if (c.y >= paddle->y() and c.y <= paddle->y() + paddle->h()){
					//check direction for bounce
					this->bounceAngle(c.direction);
					this->bouncedPaddle = true;
				}
			}
		}
	}

	else if (this->y() >= 240){

	}
}

/*
void Ball::checkOverlap(coord){

}
*/

void Ball::bounceAngle(char direction){ // ADD CORRECT ANGLES FOR NAMES OF POINTS
	if (direction == 'd'){
		this->bounceVertical();
		this->bounceHorizontal();
	}

	else if (direction == 'v'){
		this->bounceVertical();
	}

	else if (direction == 'h'){
		this->bounceHorizontal();
	}
}



#endif /* BALL_H_ */
