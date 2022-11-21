#ifndef BALL_H_
#define BALL_H_

#include <FL/Fl_Box.H>
#include "Paddle.h"
#include "Bricks.h"
#include "Brick.h"
#include <math.h>
#include <vector>
using namespace std;


//structure to save collision points of ball
struct c_point{
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

	vector<c_point> cardinals;
	vector<c_point> diagonals;


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

	//checks for collision using ball's collision points
	void checkCollision(Paddle *paddle, Bricks *bricks);

	bool bounce(Paddle *paddle, Brick *brick);

	//sets speed accordingly to angle
	void bounceAngle(char name);

	//calculate distance to brick
	//int distanceToBrick(Brick *brick);
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

	//direction component of c_point is assigned using keys around s on keyboard as reference:
	// q w e
	// a . d
	// z x c

	//cardinal c_point north
	this->cardinals.at(0).x = this->x() + this->diameter/2;
	this->cardinals.at(0).y = this->y() - margin;
	this->cardinals.at(0).direction = 'w';

	//cardinal c_point east
	this->cardinals.at(1).x = this->x() + this->diameter + margin;
	this->cardinals.at(1).y = this->y() + this->diameter/2;
	this->cardinals.at(1).direction = 'd';

	//cardinal c_point south
	this->cardinals.at(2).x = this->x() + this->diameter/2;
	this->cardinals.at(2).y = this->y() + this->diameter + margin;
	this->cardinals.at(2).direction = 'x';

	//cardinal c_point west
	this->cardinals.at(3).x = this->x() - margin;
	this->cardinals.at(3).y = this->y() + this->diameter/2;
	this->cardinals.at(3).direction = 'a';

	//diagonal c_point top-left
	this->diagonals.at(0).x = this->x() + 0.15*diameter - margin;
	this->diagonals.at(0).y = this->y() + 0.15*diameter - margin;
	this->diagonals.at(0).direction = 'q';

	//diagonal c_point top-right
	this->diagonals.at(1).x = this->x() + 0.85*diameter + margin;
	this->diagonals.at(1).y = this->y() + 0.15*diameter - margin;
	this->diagonals.at(1).direction = 'e';

	//diagonal c_point bottom-right
	this->diagonals.at(2).x = this->x() + 0.85*diameter + margin;
	this->diagonals.at(2).y = this->y() + 0.85*diameter + margin;
	this->diagonals.at(2).direction = 'c';

	//diagonal c_point bottom-left
	this->diagonals.at(3).x = this->x() + 0.15*diameter - margin;
	this->diagonals.at(3).y = this->y() + 0.85*diameter + margin;
	this->diagonals.at(3).direction = 'z';
}

void Ball::checkCollision(Paddle *paddle, Bricks *bricks){
	if (this->y() < 480 - paddle->h() - this->diameter){
		this->bouncedPaddle = false;
	}

	//paddle collision check
	if (not this->bouncedPaddle){
		this->bouncedPaddle = this->bounce(paddle, NULL);
	}
	//ADD DIFFERENT ANGLED BOUNCE FOR FRONT AND BACK END OF PADDLE

	//Brick collision
	if (this->y() < 300){
		for (Brick *brick : bricks->getBricks()){
			if (bounce(NULL, brick)){
				brick->takeDamage();
				break;
			}
		}
	}
}

/*
void Ball::checkOverlap(c_point){

}
*/

bool Ball::bounce(Paddle *paddle, Brick *brick){
	Fl_Box *object;
	if (paddle != NULL){
		object = paddle;
	}
	else if (brick != NULL){
		object = brick;
	}
	for (c_point c : this->cardinals){
		if (c.y >= object->y() and c.y <= object->y() + object->h()){
			if (c.x >= object->x() and c.x <= object->x() + object->w()){
				//set direction for bounce
				this->bounceAngle(c.direction);
				return true;
			}
		}
	}

	for (c_point c : this->diagonals){
		if (c.y >= object->y() and c.y <= object->y() + object->h()){
			if (c.x >= object->x() and c.x <= object->x() + object->w()){
				//set direction for bounce
				this->bounceAngle(c.direction);
				return true;
			}
		}
	}
	return false;
}

void Ball::bounceAngle(char direction){
	//brute force ensuring ball bounces in correct direction
	if (direction == 'q'){
		this->xSpeed = abs(this->xSpeed);
		this->ySpeed = abs(this->ySpeed);
		return;
	}
	if (direction == 'w'){
		this->ySpeed = abs(this->ySpeed);
		return;
	}
	if (direction == 'e'){
		this->xSpeed = abs(this->xSpeed) * -1;
		this->ySpeed = abs(this->ySpeed);
		return;
	}
	if (direction == 'd'){
		this->xSpeed = abs(this->ySpeed) * -1;
		return;
	}
	if (direction == 'c'){
		this->xSpeed = abs(this->xSpeed) * -1;
		this->ySpeed = abs(this->ySpeed) * -1;
		return;
	}
	if (direction == 'x'){
		this->ySpeed = abs(this->ySpeed) * -1;
		return;
	}
	if (direction == 'z'){
		this->xSpeed = abs(this->xSpeed);
		this->ySpeed = abs(this->ySpeed) * -1;
		return;
	}
	if (direction == 'a'){
		this->xSpeed = abs(this->xSpeed);
		return;
	}
}

/*
int Ball::distanceToBrick(Brick *brick){
	int distance;
	double x_diff = double(this->x() + (this->diameter/2) - brick->x() + (brick->w()/2));
	double y_diff = double(this->y() + (this->diameter/2) - brick->y() + (brick->h()/2));
	distance = sqrt(pow(x_diff,2) + pow(y_diff,2));
	return distance;
}
*/
#endif /* BALL_H_ */
