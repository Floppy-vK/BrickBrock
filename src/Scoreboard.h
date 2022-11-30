#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>
using namespace std;

class Scoreboard : public Fl_Box {
private:
	int totalScore = 0;
	string* labelText;
public:
	Scoreboard(int x, int y, string *labelText) : Fl_Box(x,y,80,40,(*labelText).c_str()){
		this->labelText = labelText;
		this->box(FL_UP_BOX);
		this->labelfont(2);
		this->updateLabel();
	}

	void addPoints(int points);
	void updateLabel();
};

void Scoreboard::addPoints(int points){
	this->totalScore = this->totalScore + points;
	*labelText = "Score: " + to_string(totalScore);
}

void Scoreboard::updateLabel(){
}

#endif /* _SCOREBOARD_H_ */
