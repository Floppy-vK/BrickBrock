#ifndef BRICKS_H_
#define BRICKS_H_

#include "Brick.h"

class Bricks{
private:
	int max_height;
	int max_width;
	Brick bricks[4][12];
public:
	Bricks(int max_width, int max_height){
		this->max_width = max_width;
		this->max_height = max_height;

		for (int h = 0; h < max_height; h++){
			for (int w = 0; w < max_width; w++){
				this->bricks[h][w].position(w*10, h*10);
				this->bricks[h][w].color(FL_YELLOW);
			}
		}
	}

	Brick* get_brick(int i, int j);

	void show_all();
};

Brick* Bricks::get_brick(int w, int h){
	return &bricks[h][w];
}

void Bricks::show_all(){
	for (int h = 0; h < max_height; h++){
		for (int w = 0; w < max_width; w++){
			this->bricks[h][w].show();
		}
	}
}

#endif /* BRICKS_H_ */
