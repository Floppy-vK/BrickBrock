#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"


class GameWindow : public Fl_Window {
private:
	Ball *ball = new Ball(30,30);
	Paddle *paddle = new Paddle(600,600);
public:
	GameWindow() : Fl_Window(100, 100, 1400, 700, "Canvas"){
		Fl::add_timeout(0.5, animate, (void*)this);
		this->init_window();
	}

	bool isRunning();
	static void animate(void *userdata);
	void init_window();
};

void GameWindow::init_window(){
	GameWindow *win = this;
	for (int i = 50; i < 850; i=i+30){
		for (int j = 50; j < 400; j=j+30){
			Brick *bricks = new Brick(i, j, 3);
			bricks->show();
		}
	}
	this->paddle->show();
	this->ball->show();
	this->ball->setSpeed(3,1);
	win->show();
}

bool GameWindow::isRunning(){
	this->ball->move();
	return true;
}

void GameWindow::animate(void *userdata){
	GameWindow *w = (GameWindow *)userdata;
	if (w->isRunning()){
		Fl::repeat_timeout(0.025, animate, userdata);
	}
}

#endif
