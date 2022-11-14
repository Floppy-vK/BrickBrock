#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"


class GameWindow : public Fl_Window {
private:
	Ball ball = Ball(30,30);
public:
	GameWindow() : Fl_Window(100, 100, 1400, 700, "Canvas"){
		this->ball.draw();
	}
};
#endif
