#ifndef BRICKS_H_
#define BRICKS_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include "Brick.h"
#include "Ball.h"
#include <vector>
using namespace std;

class Bricks{
private:
	int x_start = 30; //change to appropriate value
	int y_start = 30; //change to appropriate value
	int bricks_vert;
	int bricks_horiz;
	int brick_width = 40;
	int padding = 5;
	vector<Brick*> bricks;
public:
	Bricks(int bricks_horiz, int bricks_vert){
		this->bricks_horiz = bricks_horiz;
		this->bricks_vert = bricks_vert;

		for (int h = 0; h < bricks_vert; h++){
			for (int w = 0; w < bricks_horiz; w++){
				bricks.push_back(new Brick(0,0,this->brick_width,this->brick_width,3));
			}
		}
		this->spread_bricks();
	}

	Brick* get_brick(int index);
	void spread_bricks();
	void show_all();
};

Brick* Bricks::get_brick(int index){
	return bricks.at(index);
}

void Bricks::spread_bricks(){
	int index = 0;
	for (int b_v = 0; b_v < bricks_vert; b_v++){
		for (int b_h = 0; b_h < bricks_horiz; b_h++){
			int brick_x_pos = x_start + b_h * (this->brick_width + this->padding);
			int brick_y_pos = y_start + b_v * (this->brick_width + this->padding);
			bricks.at(index)->position(brick_x_pos, brick_y_pos);
			index++;
		}
	}
}

void Bricks::show_all(){
	for (Brick* brick : bricks){
		brick->show();
	}
}

#endif /* BRICKS_H_ */
