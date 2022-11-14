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
	return (Fl::run());
}
