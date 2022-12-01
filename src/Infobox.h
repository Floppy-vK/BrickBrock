#ifndef _INFOBOX_H_
#define _INFOBOX_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>
using namespace std;

class Infobox : public Fl_Box {
private:
	int totalScore = 0;
	string* labelText;
public:
	Infobox(int x, int y, int w, int h, string *labelText) : Fl_Box(x, y, w, h,(*labelText).c_str()){
		this->labelText = labelText;
		this->init_box();
	}

	void init_box();
	//for score box
	void addPoints(int points);
	void updateLabel();
	int getScore();
	//for end game box
	void addTime(int time);

};

void Infobox::init_box(){
	this->box(FL_EMBOSSED_BOX);
	this->labelfont(FL_COURIER + FL_BOLD);
	this->color(FL_WHITE);
}

void Infobox::addPoints(int points){
	this->totalScore = this->totalScore + points;
	string* text = this->labelText;
	*text = "Score: " + to_string(this->totalScore);
}

int Infobox::getScore(){
	return totalScore;
}

void Infobox::addTime(int time){
	string* text = this->labelText;
	*text = "Time played: " + to_string(time);
}

#endif /* _INFOBOX_H_ */
