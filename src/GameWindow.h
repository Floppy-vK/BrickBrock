#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Bricks.h"
#include "Paddle.h"


class GameWindow : public Fl_Window {
private:
	Ball *ball = new Ball(30,30);
	Paddle *paddle = new Paddle(600,600);
	Brick *brick = new Brick(20,20, 3);
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
	this->brick->show();
	this->paddle->show();
	this->ball->show();
	this->ball->setSpeed(3,1);
	win->show();
}

bool GameWindow::isRunning(){
	this->ball->move();
	redraw();
	return true;
}

void GameWindow::animate(void *userdata){
	GameWindow *w = (GameWindow *)userdata;
	if (w->isRunning()){
		Fl::repeat_timeout(0.025, animate, userdata);
	}
}

#endif /* GAMEWINDOW_H_ */
