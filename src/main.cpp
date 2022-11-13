#include <iostream>
using namespace std;

#include <FL/Fl.H>
#include <FL/fl_Draw.H>
#include "GameWindow.h"

void animate(void*){
	cout << "Tick" << endl;
}

int main(){
	GameWindow *win = new GameWindow(100, 100, 1720, 880, "Canvas");
	win->show();
	return (Fl::run());
}
