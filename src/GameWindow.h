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
	//ball object
	Ball *ball = new Ball(30, 210);
	//paddle object
	Paddle *paddle = new Paddle(260, 460, 120, 20);
	//bricks object
	Bricks *bricks = new Bricks(30, 60, 1, 1);

	//score box
	string *scoreText = new string("---Placeholder---");
	Infobox *scoreBox = new Infobox(0,0, 100, 30,  scoreText);

	//"press enter to continue" box
	Infobox *continueBox = new Infobox(220, 220, 200, 40, new string("You died!\nPress ENTER to continue"));

	//end game box
	string *endGameText = new string("--Placeholder--");
	Infobox *endGameBox = new Infobox(270, 220, 100, 40, endGameText);

	//end game box
	string *timerText = new string("--Placeholder--");
	Infobox *timerBox = new Infobox(540, 0, 100, 30, timerText);

	//maximum achievable score
	int max_score;
	//player lives
	int lives = 3;

public:
	GameWindow() : Fl_Double_Window(100, 100, 640, 480, "Canvas"){
		//start refresh rate loop (chained timeouts)
		Fl::add_timeout(0.5, animate, (void*)this);
		//hide/show all objects
		this->init_window();
		//calculate maximum score
		this->max_score = bricks->getBlockCount() * 10;
	}

	bool isRunning();
	static void animate(void *windowData);
	void init_window();
	void showEndGameBox();
};

void GameWindow::init_window(){
	//show bricks
	this->bricks->showAll();
	//show paddle
	this->paddle->show();
	//show ball and set initial speed
	this->ball->show();
	this->ball->setSpeed(4,4);
	//show score box by adding 0 to score
	this->scoreBox->addPoints(0);
	//show timer by adding 0 to time
	this->timerBox->addTime(0);
	//hide pop-up box
	this->continueBox->hide();
	//hide end of game pop-up box
	this->endGameBox->hide();
	//set background color of window
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
		this->scoreBox->addPoints(10);
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
	}
	//check if ball is alive, check for collisions, check whether bricks need to be deleted
	else if (window->isRunning()){
		window->timerBox->addTime(0.025);
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
		//reset ball
		window->ball->position(30,210);
		window->ball->setSpeed(4,4);
		window->ball->setAlive(true);
		//reset paddle
		window->paddle->position(260, 460);
		//hide pop-up box
		window->continueBox->hide();
		//continue game
		Fl::repeat_timeout(0.025, animate, windowData);
	}
	//if no more lives left and ball dies, player loses
	else{
		window->endGameBox->playerWin(false);
	}
}

#endif /* _GAMEWINDOW_H_ */
