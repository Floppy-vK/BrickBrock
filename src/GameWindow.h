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
#include <iostream>
using namespace std;

class GameWindow : public Fl_Double_Window{
private:

	Ball *ball = new Ball(30, 210);

	Paddle *paddle = new Paddle(260, 460, 120, 20);

	Bricks *bricks = new Bricks(30, 60, 13, 3);

	Fl_Box *ceilingBox = new Fl_Box(0,0,640,30);

	string *scoreText = new string("---Placeholder---");
	Infobox *scoreBox = new Infobox(0,0, 100, 30,  scoreText);


	string *timerText = new string("--Placeholder--");
	Infobox *timerBox = new Infobox(540, 0, 100, 30, timerText);


	string *livesText = new string("Lives: 3");
	Infobox *livesBox = new Infobox(270, 0, 100, 30, livesText);

	Infobox *continueBox = new Infobox(220, 220, 200, 40, new string("You died!\nPress ENTER to continue"));

	string *endGameText = new string("--Placeholder--");
	Infobox *endGameBox = new Infobox(270, 220, 100, 40, endGameText);

	//maximum achievable score
	int max_score;
	//player lives
	int lives = 3;

public:
	GameWindow() : Fl_Double_Window(100, 100, 640, 480, "BrickBrock"){
		//start refresh rate loop (chained timeouts)
		Fl::add_timeout(0.5, animate, (void*)this);
		//hide/show all objects
		this->init_window();
		//calculate maximum score
		this->max_score = this->bricks->getMaxBricks()*10;
	}

	bool isRunning();
	static void animate(void *windowData);
	void init_window();
	void showEndGameBox();
	void waitForInput(int keyCode);
};

void GameWindow::init_window(){
	Fl::set_color(FL_DARK1, 42, 52, 57);
	Fl::set_color(FL_DARK2, 31, 38, 42);

	this->bricks->showAll();

	this->paddle->show();

	this->ball->show();
	this->ball->setSpeed(4,4);

	//set up ceiling box (esthetics)
	this->ceilingBox->box(FL_UP_BOX);
	this->ceilingBox->color(FL_DARK2);

	//show score box by adding 0 to score
	this->scoreBox->setPoints(0);

	//show timer by adding 0 to time
	this->timerBox->addTime(0.5);

	this->livesBox->show();

	this->continueBox->hide();

	this->endGameBox->hide();

	//set background color of window
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

	//brute force tracking of ball
	if (not this->ball->getBouncedPaddle()){
		if (this->ball->x() + this->ball->w()/2 < this->paddle->x() + this->paddle->w()/2 - 10){
			this->paddle->moveLeft();
		}
		else if (this->ball->x() > this->paddle->x() + this->paddle->w()/2 - this->ball->w()/2 + 10){
				this->paddle->moveRight();
			}
	}

	this->ball->checkCollision(paddle, bricks);

	//check if bricks broke, if so, add points
	if(this->bricks->deleteBrick()){
		int currentScore = this->max_score - (this->bricks->getBrickCount() * 10);
		this->scoreBox->setPoints(currentScore);
	}

	//move ball, or return false if ball is "dead"
	return this->ball->move();
}

//animates the window by introducing a pseudo-refreshrate; also checks if game is running, if not, either the ball is dead or all bricks are gone
void GameWindow::animate(void *windowData){
	GameWindow *window = (GameWindow *)windowData;

	//check if player has broken all bricks
	if (window->scoreBox->getScore() >= window->max_score){
		window->endGameBox->playerWin(true);
		window->waitForInput(FL_Enter);
		window->hide();
	}
	//check if ball is alive, check for collisions, check whether bricks need to be deleted
	else if (window->isRunning()){
		window->timerBox->addTime(0.02);
		Fl::repeat_timeout(0.02, animate, windowData);
	}
	//check if player has lives, if so, wait for ENTER key and display continue box
	else if(window->lives > 0){
		window->continueBox->show();
		window->lives--;
		string* livesPointer = window->livesText;
		*livesPointer = "Lives: " + to_string(window->lives);

		window->waitForInput(FL_Enter);

		//reset ball position and speed
		window->ball->position(30,210);
		window->ball->setSpeed(4,4);
		window->ball->setAlive(true);

		//reset paddle position
		window->paddle->position(260, 460);

		window->continueBox->hide();

		//continue game
		Fl::repeat_timeout(0.025, animate, windowData);
	}
	//if no more lives left and ball dies, player loses
	else{
		window->endGameBox->playerWin(false);
		window->waitForInput(FL_Enter);
		window->hide();
	}
}

//wait for specified key-input
void GameWindow::waitForInput(int keyCode){
	while (not Fl::event_key(keyCode)){
		Fl::wait();
		continue;
	}
	return;
}

#endif /* _GAMEWINDOW_H_ */
