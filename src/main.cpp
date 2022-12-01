#include <iostream>
using namespace std;

#include <FL/Fl.H>
#include <FL/fl_Draw.H>
#include <FL/Fl_Double_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "GameWindow.h"

int main(){
	GameWindow *win = new GameWindow();
	win->show();
	return (Fl::run());
}
