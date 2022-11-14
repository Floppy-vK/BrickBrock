#include <iostream>
using namespace std;

#include <FL/Fl.H>
#include <FL/fl_Draw.H>
#include <FL/Fl_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "GameWindow.h"

int main(){
	GameWindow *win = new GameWindow();
	Ball *ball = new Ball(30,30);
	for (int i = 50; i < 850; i=i+30){
		for (int j = 50; j < 400; j=j+30){
			Brick *bricks = new Brick(i, j, 3);
			bricks->show();
		}
	}



	Paddle *paddle = new Paddle(600, 600);
	paddle->show();
	ball->show();
	win->show();
	return (Fl::run());
}
