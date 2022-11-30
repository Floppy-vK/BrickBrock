#ifndef _BALL_H_
#define _BALL_H_

#include <FL/Fl_Box.H>
#include "Paddle.h"
#include "Bricks.h"
#include "Brick.h"
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;


//structure to save collision points of ball
struct c_point{
	int x;
	int y;
	char direction;
};

struct speed_vector{
	int v_x;
	int v_y;
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

	int x_speeds[9] = {6, 5, 4, 2, 0,-2,-4,-5,-6};
	int y_speeds[9] = {0, 2, 4, 5, 6, 5, 4, 2, 0};

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

	void setSpeed(int v_x, int v_y);

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

	c_point checkOverlapPoints(vector<c_point> points, Fl_Box *object);

	bool bounceBrick(Brick *brick);

	bool bouncePaddle(Paddle *paddle);

	//sets speed accordingly to angle
	void bounceAngle(char name);

	//calculate distance to brick
	//int distanceToBrick(Brick *brick);
};


//Function definitions

void Ball::setSpeed(int v_x, int v_y){
	this->xSpeed = v_x;
	this->ySpeed = v_y;
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
	int margin = this->diameter + 5;
	if (this->y() + margin < paddle->y() or this->x() + margin < paddle->x() or this->x() > paddle->x() + paddle->w() + 5){
		this->bouncedPaddle = false;
	}

	//paddle collision check
	if (not this->bouncedPaddle){
		this->bouncedPaddle = this->bouncePaddle(paddle);
	}

	//Brick collision check
	if (this->y() < 300){
		for (Brick *brick : bricks->getBricks()){
			if (bounceBrick(brick)){
				brick->takeDamage();
				break;
			}
		}
	}
}

c_point Ball::checkOverlapPoints(vector<c_point> points, Fl_Box *object){
	c_point nullPoint;
	nullPoint.direction = 'n';
	for (c_point c : points){
		if (c.y >= object->y() and c.y <= object->y() + object->h()){
			if (c.x >= object->x() and c.x <= object->x() + object->w()){
				return c;
			}
		}
	}
	return nullPoint;
}

bool Ball::bouncePaddle(Paddle *paddle){
	c_point point = checkOverlapPoints(this->cardinals, paddle);
	int index;

	if (point.direction == 'n'){
		point = checkOverlapPoints(this->diagonals, paddle);
	}
	if (point.direction != 'n'){
		auto it = find(begin(this->x_speeds), end(this->x_speeds), this->xSpeed);
		if (it != end(this->x_speeds)) {
			index = distance(this->x_speeds, it);
		}

		if (point.x <= paddle->x() + 0.2 * paddle->w()){
			index++;
			if (index > 8){
				index = 0;
			}
		}
		else if (point.x >= paddle->x() + 0.8 * paddle->w()){
			index--;
			if (index < 0){
				index = 8;
			}
		}
		this->setSpeed(this->x_speeds[index], this->y_speeds[index]);
		this->bounceAngle(point.direction);
		return true;
	}
	return false;
}

bool Ball::bounceBrick(Brick *brick){
	c_point point = checkOverlapPoints(this->cardinals, brick);
	if (point.direction == 'n'){
		point = checkOverlapPoints(this->diagonals, brick);
	}

	if (point.direction != 'n'){
		this->bounceAngle(point.direction);
		return true;
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

#endif /* _BALL_H_ */
