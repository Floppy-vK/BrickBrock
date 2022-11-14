#ifndef BLOCK_H_
#define BLOCK_H_

#include <FL/Fl_Box.H>

class Block : public Fl_Box{
private:
	//coordinates
	int x;
	int y;

public:
	void setCoords(int x, int y);

	Block(int x, int y, int w, int h, Fl_Boxtype blockType = FL_NO_BOX, Fl_Color color = FL_WHITE): Fl_Box(x, y, w, h){
		this->x = x;
		this->y = y;
		this->box(blockType);
		this->color(color);
	}


};

void Block::setCoords(int x, int y){
	this->hide();
	this->x = x;
	this->y = y;
	this->position(x, y);
	this->show();
}

#endif /* BLOCK_H_ */
