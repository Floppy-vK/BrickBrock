#ifndef BRICK_H_
#define BRICK_H_

#include <FL/Fl_Box.H>

class Brick : public Fl_Box{
private:
	int hitPoints;
	bool isAlive = true;

public:
	Brick(int x, int y, int width, int height, int hitPoints) : Fl_Box(x, y, width, height){
		this->box(FL_THIN_UP_BOX);
		this->color(FL_YELLOW);
		this->hitPoints = hitPoints;
		this->labelfont(1);
		this->updateLabel();
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
	void updateLabel();
};

void Brick::takeDamage(){
	this->hitPoints--;
	this->updateLabel();
	if (hitPoints <= 0){
		this->isAlive = false;
	}
}

bool Brick::getIsAlive(){
	return isAlive;
}

void Brick::updateLabel(){
	if (hitPoints <= 0){
		this->isAlive = false;
	}
	if (this->hitPoints == 2){
		this->label("2");
	}
	if (this->hitPoints == 1){
		this->label("1");
	}
	if (this->hitPoints <= 0){
		this->label("");
		this->isAlive = false;
		this->box(FL_NO_BOX);
	}
}


#endif /* BRICK_H_ */
