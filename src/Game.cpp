#include <GL/glut.h>
#include <stdio.h>
#include <list>
#include <vector>
#include "Game.h"
#include <iostream>
#include "camera/Camera3D_1.h"
#include "light/DirecLight.h"

static std::vector<Ghost *> *ghosts;	// Ponteiro para vector que contém os fantasmas
static int timers = 0;					// Número de timers

Game::Game() : _ghosts(), _balls(), _time(0), _gameOver(false), _gameWin(false) {
	srand ( time(NULL) );
	_board = new Board();
	_pacman = new PacmanP1(0, 2);
  	_light = new DirecLight();
	_camera = new Camera3D_1(this);
	_scoreBoard = new ScoreBoard();
	float ghostscolor[3][3] = {{1. , 0. , 0.}, {0. , 1. , 0.}, {0. , 0. , 1.}};
	for(int i = -1; i <= 1; i++) {
		_ghosts.push_back(new Ghost(i, 0, _pacman->getPos(), ghostscolor[i+1] ));
	}
	createBalls();
	_nBalls = _balls.size();
	ghosts = &_ghosts;
}

void Game::draw(bool help){
	_camera->setCamera();
	_light->giveLight();
	_board->draw();
	std::list<Ball *>::iterator it;
	for(it = _balls.begin(); it != _balls.end(); it++) {
		(*it)->draw();
	}
	for(int i = 0; i < _ghosts.size(); i++) {
		_ghosts[i]->draw();
	}
	_pacman->draw(_gameOver, _gameWin);
	_scoreBoard->showScore(help, _gameOver, _gameWin);
}

bool Game::moves(char key, char p2key, long unsigned int t){
	long unsigned int dt = 0;
	int Ndirection = 0;
	int direction = 0;
	dt = t - _time;
	_time = t;
	if(_gameOver){
		_pacman->premove(dt);					//Posição final pretendida pelo Pacman
		return true;
	}
	position pacDest, NpacDest;
	position pacOrig, NpacOrig;
	position ghostxDest;
	pacOrig = _pacman->getPos();					//Posição inicial do Pacman
	pacDest = _pacman->premove(dt);					//Posição final pretendida pelo Pacman
	pacDest = _board->checkPacmanPath(pacOrig, pacDest, key, &direction, this);	//Chamada á função de verificação do caminho pretendido
	if(direction != 0)
		_pacman->setDirection(direction);
	if(_pacman->isDirectionSet()){
		_pacman->move(pacDest);
		if(!_pacman->isDead()) _light->setupLight(_pacman->getPos(), _pacman->getDirection());		// Actualização da Luz
		for(int i = 0; i < _ghosts.size(); i++) {
			char ghostDir;
			ghostxDest = _ghosts[i]->premove(dt, pacDest, &ghostDir);
			ghostxDest = _board->checkGhostPath(_ghosts[i]->getPos(), ghostxDest, ghostDir, &direction, this);	//Chamada á função de verificação do caminho pretendido
			if(direction != 0)
				_ghosts[i]->setDirection(direction);
			if(_ghosts[i]->isDirectionSet())
				_ghosts[i]->move(ghostxDest);
			_ghosts[i]->lookToPacman(pacDest);
			if(_board->checkColision(ghostxDest, pacDest)){		// checkColision(Board_colisions.cpp) -> Verificação se há colisão
				colision(i);	// Se houver colisão, trata-se a colisão do fantasma correspondente
			} 
		}
		if(!_pacman->isDead()) _camera->update(this, dt);
		return true;
	}
	return false;
}

void Game::stopPacman(){
	_pacman->stop();
}

void Game::pacmanSetDirection(int i){
	_pacman->setDirection(i);
}

void Game::createBalls(){
	Ball *  b;
	for (int x = -11; x <= 11; x++) {
		for (int y = -6; y <= 6; y++) {
			if((y == -6 || y == 6) && (x == -5 || x == 5))
				continue;
			else if((y == -5 || y == 5) && (x == -10 || x == -9 || x == -7 || x == -5 || x == -3 || x == -2 || x == -1 || x == 0 || x == 1 || x == 2 || x == 3 || x == 5 || x == 7 || x == 9 || x == 10))
				continue;
			else if((y == -4 || y == 4) && (x == -10 || x == -9 || x == -7 || x == -3 || x == 3 || x == 7 || x == 9 || x == 10))
				continue;
			else if((y == -3 || y == 3) && (x == -7 || x == -6 || x == -5 || x == -3 || x == -1 || x == 0 || x == 1 || x == 3 || x == 5 || x == 6 || x == 7))
				continue;
			else if((y == -2 || y == 2) && (x == -10 || x == -8 || x == -7 || x == 7 || x == 8 || x == 10))
				continue;
			else if((y == -1 || y == 1) && (x == -10 || x == -8 || x == -7 ||x == -5 || x == -4 || x == -2 || x == -1 || x == 0 || x == 1 || x == 2 || x == 4 ||x == 5 || x == 7 || x == 8 || x == 10))
				continue;
			else if((x == 0 && y == 2) || ((y == 0) && (x == -10 || x == -5 || x == -4 || x == -2  || x == -1 || x == 0 || x == 1 || x == 2 || x == 4 || x == 5 || x == 10)))
				continue;
			else if ((x== -11 || x==11) && (y ==-6 || y == 6))
				b= new Ball(x, y, 400, true);
			else
				b = new Ball(x, y);
			_balls.push_back(b);
			_board->addBall(x, y, b);
		}
	}
}


inline void Game::drawPoints(){
	glPushMatrix();
		glColor3f(1.,1.,1.);
		glBegin(GL_POINTS);
		for(float i = -13.; i <= 13. ; i++){
			for(float j = -8.; j <= 8. ; j++){
				glVertex3f(i, j, 2.0f);
			}
		}
		glEnd();
	glPopMatrix();
}

void Game::panicModeOff(int value){
	timers--;
	if(!timers){
		for(int i = 0; i < ghosts->size(); i++) {
			ghosts->at(i)->unsetState();
		}	
	}
}

void Game::changeState(){
	timers++; // Incrementa o número de timers 
	for(int i = 0; i < _ghosts.size(); i++) {
		_ghosts[i]->setState();
	}
	glutTimerFunc(10000, Game::panicModeOff, 1);		// Função panicModeOff vai ser executada durante pelo menos, 10000ms (10s)
}


void Game::colision(int i){
	if(_ghosts[i]->isEatable()){
		_ghosts[i]->die();
		_scoreBoard->add(1000);
	}else{
		if(!_pacman->isDead()){
			_pacman->bang();
			_gameOver = _scoreBoard->killLives();
		}
	}
}

void Game::ballEaten() {
	if(--_nBalls == 0) {
		_gameOver = true;
		_gameWin = true;
	}
}
