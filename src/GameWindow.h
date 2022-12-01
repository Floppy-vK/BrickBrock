#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Ball.h"
#include "Brick.h"
#include "Bricks.h"
#include "Paddle.h"
#include "Infobox.h"
#include <string>
using namespace std;

class GameWindow : public Fl_Double_Window{
private:
	Ball *ball = new Ball(30, 210);
	Paddle *paddle = new Paddle(260, 460, 120, 20);
	Bricks *bricks = new Bricks(30, 60, 1, 1);

	//score box
	string *scoreText = new string("Score: 0");
	Infobox *scorebox = new Infobox(0,0, 100, 30,  scoreText);

	//"press enter to continue" box
	Infobox *continueBox = new Infobox(220, 220, 200, 40, new string("You died!\nPress ENTER to continue"));

	//end game box
	string *winText = new string("You win! Time played: ");
	Infobox *endGameBox = new Infobox(230, 220, 180, 40, winText);

	int max_score;
	int lives = 3;

public:
	GameWindow() : Fl_Double_Window(100, 100, 640, 480, "Canvas"){
		Fl::add_timeout(0.5, animate, (void*)this);
		this->init_window();
		this->max_score = bricks->getBlockCount() * 10;
	}

	bool isRunning();
	static void animate(void *windowData);
	void init_window();
};

void GameWindow::init_window(){
	this->bricks->showAll();
	this->paddle->show();
	this->ball->show();
	this->ball->setSpeed(4,4);
	this->scorebox->show();
	this->continueBox->hide();
	this->endGameBox->hide();
	Fl::set_color(FL_DARK1, 42, 52, 57);
	this->color(FL_DARK1);
	this->show();
}

//check if ball is alive, check for collisions, check whether bricks need to be deleted
bool GameWindow::isRunning(){
	//take player input
	if (Fl::event_key(FL_Right)){
		this->paddle->moveRight();
	}
	if (Fl::event_key(FL_Left)){
		this->paddle->moveLeft();
	}

	/*
	//BRUTE FORCE TRACKING BALL
	if (this->ball->x() < this->paddle->x() + this->paddle->w()/2){
		this->paddle->moveLeft();
	}
	else if (this->ball->x()  > this->paddle->x() + this->paddle->w()/2 - this->ball->w()){
			this->paddle->moveRight();
		}
	*/

	//check collision of ball with paddle and bricks
	this->ball->checkCollision(paddle, bricks);
	//check if bricks broke, if so, add points
	if(this->bricks->deleteBrick()){
		this->scorebox->addPoints(10);
	}
	//move ball, or return false if ball is "dead"
	return this->ball->move();
}

void GameWindow::animate(void *windowData){
	GameWindow *window = (GameWindow *)windowData;
	if (window->scorebox->getScore() >= window->max_score){
		window->winText = new string("You win! Time Played: " + to_string(100));
		window->endGameBox->show();
		return;
	}
	//check if ball is alive, check for collisions, check whether bricks need to be deleted
	else if (window->isRunning()){
		Fl::repeat_timeout(0.025, animate, windowData);
	}
	//check if player has lives, if so, wait for ENTER key
	else if(window->lives > 0){
		window->continueBox->show();
		window->lives--;
		while (not Fl::event_key(FL_Enter)){
			Fl::wait();
			continue;
		}
		window->ball->setSpeed(4,4);
		window->ball->setAlive(true);
		window->continueBox->hide();
		window->ball->position(30,210);
		Fl::repeat_timeout(0.025, animate, windowData);
		return;
	}
	else{

	}
}

#endif /* _GAMEWINDOW_H_ */
