#ifndef _INFOBOX_H_
#define _INFOBOX_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>
using namespace std;

class Infobox : public Fl_Box {
private:
	int totalScore = 0;
	double totalTime = 0;
	string* labelText;
public:
	Infobox(int x, int y, int w, int h, string *labelText) : Fl_Box(x, y, w, h,(*labelText).c_str()){
		this->labelText = labelText;
		this->init_box();
	}

	void init_box();
	//for score box
	void addPoints(int points);

	int getScore();
	//for end game box
	void addTime(double seconds);

	int getTime();

	void playerWin(bool win);

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

void Infobox::addTime(double seconds){
	this->totalTime = this->totalTime + seconds;
	string* text = this->labelText;
	*text = "Time: " + to_string(int(this->totalTime));
}

int Infobox::getTime(){
	return int(this->totalTime);
}

void Infobox::playerWin(bool win){
	string* text = this->labelText;
	if (win){
		*text = "YOU WIN!";

	}
	else {
		*text = "GAME OVER";
	}
	this->show();
}

#endif /* _INFOBOX_H_ */
