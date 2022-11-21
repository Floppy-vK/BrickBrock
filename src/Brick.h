#ifndef BRICK_H_
#define BRICK_H_

#include <FL/Fl_Box.H>
#include "Bricks.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Brick : public Fl_Box{
private:
	int hitPoints;
	bool isAlive = true;

public:
	Brick(int x, int y, int width, int height, int hitPoints) : Fl_Box(x, y, width, height){
		this->box(FL_THIN_UP_BOX);
		this->color(FL_GREEN);
		this->hitPoints = hitPoints;
		this->updateBrick();
	}

	void takeDamage(Bricks* bricks);
	bool getIsAlive();
	void updateBrick();
};

void Brick::takeDamage(Bricks* bricks){
	this->hitPoints--;
	this->updateBrick();
	if (hitPoints <= 0){
		//delete brick from bricks
		vector<Brick*>::iterator new_end;
		if (bricks->getBricks().back() == this){
			bricks->getBricks().pop_back();
		}
		else{
			new_end = remove(bricks->getBricks().begin(), bricks->getBricks().end(), this);
		}
	}
}

bool Brick::getIsAlive(){
	return isAlive;
}

void Brick::updateBrick(){
	if (hitPoints <= 0){
		this->isAlive = false;
	}
	if (this->hitPoints == 2){
		this->color(FL_YELLOW);
	}
	if (this->hitPoints == 1){
		this->color(FL_RED);
	}
	if (this->hitPoints <= 0){
		this->label("");
		this->isAlive = false;
		this->box(FL_NO_BOX);
	}
}


#endif /* BRICK_H_ */
