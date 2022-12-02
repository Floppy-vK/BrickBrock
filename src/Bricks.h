#ifndef _BRICKS_H_
#define _BRICKS_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include "Brick.h"
#include "Ball.h"
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class Bricks{
private:
	int x_start; //change to appropriate value
	int y_start; //change to appropriate value
	int bricks_vert;
	int bricks_horiz;
	int brick_width = 40;
	int padding = 5;
	vector<Brick*> bricks;

public:
	Bricks(int x_start, int y_start, int bricks_horiz, int bricks_vert){
		this->x_start = x_start;
		this->y_start = y_start;
		this->bricks_horiz = bricks_horiz;
		this->bricks_vert = bricks_vert;

		for (int h = 0; h < bricks_vert; h++){
			for (int w = 0; w < bricks_horiz; w++){
				int integrity = 10;
				if (h == 1){
					integrity = 5;
				}
				else if (h == 2){
					integrity = 2;
				}
				bricks.push_back(new Brick(0,0,this->brick_width,this->brick_width,integrity));
			}
		}
		this->spreadBricks();
	}

	Brick* getBrick(int index);
	vector<Brick*> getBricks();
	void spreadBricks();
	void showAll();
	bool deleteBrick();
	bool getBrickAlive(Brick *brick);
	int getBlockCount();
};

Brick* Bricks::getBrick(int index){
	return bricks.at(index);
}

vector<Brick*> Bricks::getBricks(){
	return this->bricks;
}

void Bricks::spreadBricks(){
	int index = 0;
	for (int bricksVertical = 0; bricksVertical < this->bricks_vert; bricksVertical++){
		for (int bricksHorizontal = 0; bricksHorizontal < this->bricks_horiz; bricksHorizontal++){
			int brick_x_pos = this->x_start + bricksHorizontal * (this->brick_width + this->padding);
			int brick_y_pos = this->y_start + bricksVertical * (this->brick_width + this->padding);
			bricks.at(index)->position(brick_x_pos, brick_y_pos);
			index++;
		}
	}
}

void Bricks::showAll(){
	for (Brick* brick : this->bricks){
		brick->show();
	}
}

bool Bricks::getBrickAlive(Brick *brick){
	return not brick->getIsAlive();
}

bool Bricks::deleteBrick(){
	for (Brick *brick : this->bricks){
		if (not brick->getIsAlive()){
			vector<Brick*>::iterator new_end;
			//if (this->bricks.front() == brick){
			// second element becomes first element
			//}
			if (this->bricks.back() == brick){
				this->bricks.pop_back();
			}
			else{
				new_end = remove(this->bricks.begin(), this->bricks.end(), brick);
			}
			return true;
		}
	}
	return false;
}

int Bricks::getBlockCount(){
	return this->bricks_horiz * this->bricks_vert;
}

#endif /* _BRICKS_H_ */
