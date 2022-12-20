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
	char signifier;
};

class Ball : public Fl_Box{
private:
	int min_x = 0;
	int max_x = 640;
	int min_y = 30;
	int max_y = 480;
	int x_speed;
	int y_speed;
	int diameter;

	//pre-determined x/y speed combinations with approximately appropriate angles: 0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, and 180 degrees respectively.
	int x_speeds[9] = {6, 5, 4, 2, 0,-2,-4,-5,-6};
	int y_speeds[9] = {0, 2, 4, 5, 6, 5, 4, 2, 0};

	bool isAlive = true;
	bool bouncedPaddle = false;

	//vectors of collision points
	vector<c_point> cardinals;
	vector<c_point> diagonals;

public:
	Ball(int x, int y, int diameter = 20): Fl_Box(x, y, diameter, diameter){
		this->diameter = diameter;
		this->x_speed = 0;
		this->y_speed = 0;
		this->box(FL_OVAL_BOX);
		this->color(FL_RED);
		this->cardinals.resize(4);
		this->diagonals.resize(4);
	}

	//sets speed of ball
	void setSpeed(int x_speed, int y_speed);

	//repositions ball
	bool move();

	//sets alive state of ball
	void setAlive(bool alive);

	//checks if the ball must bounce against walls
	void checkWallBounce();

	//sets new collision point locations
	void setNewCPoints();

	//checks for collision using ball's collision points
	void checkCollision(Paddle *paddle, Bricks *bricks);

	//checks if points overlap with given object
	c_point checkOverlapPoints(vector<c_point> points, Fl_Box *object);

	//checks if ball should bounce off a brick
	bool bounceBrick(Brick *brick);

	//checks if ball should bounce off of paddle
	bool bouncePaddle(Paddle *paddle);

	//sets speed accordingly to angle
	void bounceAngle(char name);

	//return bouncedPaddle boolean
	bool getBouncedPaddle();

};

//sets speed of ball
void Ball::setSpeed(int x_speed, int y_speed){
	this->x_speed = x_speed;
	this->y_speed = y_speed;
}

//checks for collision with wall, if no collision, move ball normally, set new locations for collision points
bool Ball::move(){
	this->hide();
	int new_x;
	int new_y;

	this->checkWallBounce();

	new_x = this->x() + this->x_speed;
	new_y = this->y() + this->y_speed;

	this->position(new_x, new_y);
	//sets new locations for collision points
	this->setNewCPoints();
	this->show();
	return this->isAlive;
}

//sets isAlive state of ball
void Ball::setAlive(bool alive){
	this->isAlive = alive;
}


//checks if ball hits wall, if so, it bounces off
void Ball::checkWallBounce(){
	if (this->x() >= this->max_x - this->diameter){
			this->x_speed = abs(this->x_speed)*-1;
	}
	else if (this->x() <= this->min_x){
				this->x_speed = abs(this->x_speed);
		}
	if (this->y() <= this->min_y){
			this->y_speed = abs(this->y_speed);
	}
	else if (this->y() >= this->max_y - this->diameter){
		this->isAlive = false;
	}
}

//sets up collision points around circumference of ball, in eight positions. Each of the cardinal directions has a point, and in-between those are four diagonal points.
void Ball::setNewCPoints(){
	int margin = 1;
	int radius = diameter/2;
	int diameter = this->diameter;

	//signifier component of c_point is assigned using keys around 's' key on keyboard as reference:
	// q w e
	// a . d
	// z x c

	//cardinal c_point north
	this->cardinals.at(0).x = this->x() + radius;
	this->cardinals.at(0).y = this->y() - margin;
	this->cardinals.at(0).signifier = 'w';

	//cardinal c_point east
	this->cardinals.at(1).x = this->x() + diameter + margin;
	this->cardinals.at(1).y = this->y() + radius;
	this->cardinals.at(1).signifier = 'd';

	//cardinal c_point south
	this->cardinals.at(2).x = this->x() + radius;
	this->cardinals.at(2).y = this->y() + diameter + margin;
	this->cardinals.at(2).signifier = 'x';

	//cardinal c_point west
	this->cardinals.at(3).x = this->x() - margin;
	this->cardinals.at(3).y = this->y() + radius;
	this->cardinals.at(3).signifier = 'a';

	//diagonal c_point top-left
	this->diagonals.at(0).x = this->x() + 0.15*diameter - margin;
	this->diagonals.at(0).y = this->y() + 0.15*diameter - margin;
	this->diagonals.at(0).signifier = 'q';

	//diagonal c_point top-right
	this->diagonals.at(1).x = this->x() + 0.85*diameter + margin;
	this->diagonals.at(1).y = this->y() + 0.15*diameter - margin;
	this->diagonals.at(1).signifier = 'e';

	//diagonal c_point bottom-right
	this->diagonals.at(2).x = this->x() + 0.85*diameter + margin;
	this->diagonals.at(2).y = this->y() + 0.85*diameter + margin;
	this->diagonals.at(2).signifier = 'c';

	//diagonal c_point bottom-left
	this->diagonals.at(3).x = this->x() + 0.15*diameter - margin;
	this->diagonals.at(3).y = this->y() + 0.85*diameter + margin;
	this->diagonals.at(3).signifier = 'z';
}

//checks if ball collides/overlaps with paddle or bricks in current frame
void Ball::checkCollision(Paddle *paddle, Bricks *bricks){
	int margin = this->diameter;

	//ensures ball doesn't bounce twice on paddle in subsequent frames
	if (this->y() + margin + 5 < paddle->y() or this->x() + margin < paddle->x() or this->x() > paddle->x() + paddle->w() + 5){
		this->bouncedPaddle = false;
	}

	//paddle collision check
	if (not this->bouncedPaddle){
		this->bouncedPaddle = this->bouncePaddle(paddle);
	}

	//Brick collision check
	if (this->y() < 300){
		for (Brick *brick : bricks->getBricks()){
			if (this->bounceBrick(brick)){
				brick->takeDamage();
				break;
			}
		}
	}
}

//checks for each point in vector if it overlaps with the given object's area. If a point overlaps, function returns said point, if none overlap, function return so-called nullPoint (signifier = 'n')
c_point Ball::checkOverlapPoints(vector<c_point> points, Fl_Box *object){
	c_point nullPoint;
	nullPoint.signifier = 'n';
	for (c_point c : points){
		if (c.y >= object->y() and c.y <= object->y() + object->h()){
			if (c.x >= object->x() and c.x <= object->x() + object->w()){
				return c;
			}
		}
	}
	return nullPoint;
}

//checks whether ball overlaps with and should bounce off paddle in current frame, uses cardinal and diagonal collision points to check
bool Ball::bouncePaddle(Paddle *paddle){
	c_point point = checkOverlapPoints(this->cardinals, paddle);
	int index;

	if (point.signifier == 'n'){
		point = checkOverlapPoints(this->diagonals, paddle);
	}
	if (point.signifier != 'n'){
		auto it = find(begin(this->x_speeds), end(this->x_speeds), this->x_speed);
		if (it != end(this->x_speeds)) {
			index = distance(this->x_speeds, it);
		}

		//if ball bounces on first 20% of paddle, subtract 22.5 degrees from angle of bounce (using pre-determined speeds)
		if (point.x <= paddle->x() + 0.2 * paddle->w()){
			index++;
			if (index > 8){
				index = 8;
			}
		}
		//if ball bounces on last 20% of paddle, add 22.5 degrees to angle of bounce (using pre-determined speeds)
		else if (point.x >= paddle->x() + 0.8 * paddle->w()){
			index--;
			if (index < 0){
				index = 0;
			}
		}
		this->setSpeed(this->x_speeds[index], this->y_speeds[index]);
		this->bounceAngle(point.signifier);
		return true;
	}
	return false;
}

//check if ball overlaps with and should bounce off a brick in the current frame (is called for all bricks in window)
bool Ball::bounceBrick(Brick *brick){
	c_point point = checkOverlapPoints(this->cardinals, brick);
	if (point.signifier == 'n'){
		point = checkOverlapPoints(this->diagonals, brick);
	}

	if (point.signifier != 'n'){
		this->bounceAngle(point.signifier);
		return true;
	}

	return false;
}

//brute force ensuring ball bounces in correct direction
void Ball::bounceAngle(char signifier){
	if (signifier == 'q'){
		this->x_speed = abs(this->x_speed);
		this->y_speed = abs(this->y_speed);
		return;
	}
	else if (signifier == 'w'){
		this->y_speed = abs(this->y_speed);
		return;
	}
	else if (signifier == 'e'){
		this->x_speed = abs(this->x_speed) * -1;
		this->y_speed = abs(this->y_speed);
		return;
	}
	else if (signifier == 'd'){
		this->x_speed = abs(this->x_speed) * -1;
		return;
	}
	else if (signifier == 'c'){
		this->x_speed = abs(this->x_speed) * -1;
		this->y_speed = abs(this->y_speed) * -1;
		return;
	}
	else if (signifier == 'x'){
		this->y_speed = abs(this->y_speed) * -1;
		return;
	}
	else if (signifier == 'z'){
		this->x_speed = abs(this->x_speed);
		this->y_speed = abs(this->y_speed) * -1;
		return;
	}
	else if (signifier == 'a'){
		this->x_speed = abs(this->x_speed);
		return;
	}
}

bool Ball::getBouncedPaddle(){
	return this->bouncedPaddle;
}

#endif /* _BALL_H_ */
