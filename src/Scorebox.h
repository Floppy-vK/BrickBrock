#ifndef _SCOREBOX_H_
#define _SCOREBOX_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>
using namespace std;

class Scorebox : public Fl_Box {
private:
	int totalScore = 0;
	string* labelText;
public:
	Scorebox(int x, int y, string *labelText) : Fl_Box(x,y,80,40,(*labelText).c_str()){
		this->labelText = labelText;
		this->box(FL_UP_BOX);
		this->labelfont(2);
		this->updateLabel();
	}

	void addPoints(int points);
	void updateLabel();
};

void Scorebox::addPoints(int points){
	this->totalScore = this->totalScore + points;
	*labelText = "Score: " + to_string(totalScore);
}

#endif /* _SCOREBOX_H_ */
