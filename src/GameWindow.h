#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Bricks.h"
#include "Paddle.h"
#include "Scoreboard.h"
#include <string>
using namespace std;

class GameWindow : public Fl_Window {
private:
	Ball *ball = new Ball(30, 210);
	Paddle *paddle = new Paddle(260, 460, 120, 20);
	Bricks *bricks = new Bricks(13, 3);
	string *scoreText = new string("Score: 0");
	Scoreboard *scoreboard = new Scoreboard(0,0, scoreText);
public:
	GameWindow() : Fl_Window(100, 100, 640, 480, "Canvas"){
		Fl::add_timeout(0.5, animate, (void*)this);
		this->init_window();

	}

	bool isRunning();
	static void animate(void *windowData);
	void init_window();
};

void GameWindow::init_window(){
	GameWindow *win = this;
	this->bricks->showAll();
	this->paddle->show();
	this->ball->show();
	this->ball->setSpeed(4,4);
	this->scoreboard->show();
	Fl::set_color(FL_DARK1, 42, 52, 57);
	win->color(FL_DARK1);
	win->show();
}

bool GameWindow::isRunning(){
	if (Fl::event_key(FL_Right)){
		this->paddle->moveRight();
	}
	if (Fl::event_key(FL_Left)){
			this->paddle->moveLeft();
	}

	/* BRUTE FORCE TRACKING BALL
	if (this->ball->x() < this->paddle->x()){
		this->paddle->moveLeft();
	}
	if (this->ball->x()  > this->paddle->x()){
			this->paddle->moveRight();
		}
	*/

	this->ball->checkCollision(paddle, bricks);
	if(this->bricks->deleteBrick()){
		this->scoreboard->addPoints(10);
	}
	return this->ball->move();
}

void GameWindow::animate(void *windowData){
	GameWindow *window = (GameWindow *)windowData;
	if (window->isRunning()){
		Fl::repeat_timeout(0.025, animate, windowData);
	}
	else{
		//Display GAME OVER screen
	}
}

#endif /* _GAMEWINDOW_H_ */
