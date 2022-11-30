#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>
using namespace std;

class Scoreboard : Fl_Box {
private:

public:
	Scoreboard(int x, int y) : Fl_Box(x,y,100,100) {
		this->box(FL_UP_BOX);
		this->label("Score: 0");
	}

	addPoints(int points);
};


#endif /* _SCOREBOARD_H_ */
