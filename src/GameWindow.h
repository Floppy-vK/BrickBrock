#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Paddle.h"
#include "Ball.h"

class GameWindow : public Fl_Window {
private:
	Ball ball = Ball(30,30);
public:
	static void animate(void *userdata);

	bool isRunning();

	GameWindow(int x, int y, int w, int h, const char* title=0) : Fl_Window(x, y, w, h, title){
		Fl::add_timeout(0.5, animate, (void*)this);
		this->show();
		this->ball.setSpeed(1,0);
	}

};

void GameWindow::animate(void *userdata){
	GameWindow *win = (GameWindow *)userdata;
	while(win->isRunning()){
		Fl::repeat_timeout(0.025, animate, userdata);
	}
}

bool GameWindow::isRunning(){
	if (true) {
		this->ball.move();
		if (!true) {
			return false;
		}
	}
	return true;
}

#endif
