#ifndef _BRICK_H_
#define _BRICK_H_

#include <FL/Fl_Box.H>
#include <string>
using namespace std;

class Brick : public Fl_Box{
private:
	int hitPoints;
	bool isAlive = true;
	string* hpText = new string("---");

public:
	Brick(int x, int y, int width, int height, int hitPoints) : Fl_Box(x, y, width, height){
		this->box(FL_THIN_UP_BOX);
		this->color(FL_RED);
		this->hitPoints = hitPoints;
		this->label((*hpText).c_str());
		this->labelfont(FL_COURIER_BOLD);
		this->updateBrick();
		if (hitPoints == 5){
			this->color(FL_GREEN);
		}
		if (hitPoints == 2){
			this->color(FL_YELLOW);
		}
	}

	/*
	Brick() : Fl_Box(0, 0, 40, 40){
		this->x = 0;
		this->y = 0;
		this->width = 40;
		this->height = 40;
		this->box(FL_THIN_UP_BOX);
		this->color(FL_YELLOW);
		this->hitPoints = hitPoints;
		this->labelfont(1);
		if (hitPoints == 3){
			this->label("3");
		}
	}
	*/

	void takeDamage();
	bool getIsAlive();
	void updateBrick();
};

void Brick::takeDamage(){
	this->hitPoints--;
	this->updateBrick();
	if (this->hitPoints <= 0){
		this->isAlive = false;
	}
}

bool Brick::getIsAlive(){
	return isAlive;
}

void Brick::updateBrick(){
	if (this->hitPoints > 0){
		int color = this->color();
		int new_color = fl_lighter(color);
		this->color(new_color);
		string* hpPointer = this->hpText;
		*hpPointer = to_string(this->hitPoints).c_str();
	}

	if (this->hitPoints <= 0){
		this->label("");
		this->isAlive = false;
		this->box(FL_NO_BOX);
	}
}


#endif /* _BRICK_H_ */
