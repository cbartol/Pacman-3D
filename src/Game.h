#ifndef __GAME_H__
#define __GAME_H__

#ifndef DEV_MODE
	#define DEV_MODE false
#endif
#ifndef SHOW_BOARD
	#define SHOW_BOARD true
#endif
#ifndef SHOW_PACMAN
	#define SHOW_PACMAN true
#endif
#ifndef SHOW_GHOST
	#define SHOW_GHOST false
#endif
#ifndef SHOW_BALLS
	#define SHOW_BALLS true
#endif
#include "conventions.h"
#include "Board.h"
#include "entity/Pacman.h"
#include "entity/PacmanP1.h"
#include "entity/PacmanP2.h"
#include "Ball.h"
#include "entity/Ghost.h"
#include "ScoreBoard.h"
#include <list>
#include <vector>
#include "camera/Camera.h"
#include "light/Light.h"

#include <stdlib.h>
#include <time.h>


class Game{
	private:
		Camera *_camera;
		Board * _board;
		Pacman * _pacman;
//		Pacman * _darkpacman;
		Light *_light;
		ScoreBoard *_scoreBoard;
		std::list<Ball *>  _balls;
		std::vector<Ghost *> _ghosts;
		long unsigned int _time;
		int _nBalls;
		bool _gameOver, _gameWin;
	public:	
		Game();
		~Game(){
			int i, size;
			delete _camera;
			delete _board;
			delete _pacman;
	//		delete _darkpacman;
			delete _light;
			delete _scoreBoard; 
			std::list<Ball *>::iterator it;
			for(it = _balls.begin(); it != _balls.end(); it++) {
				delete (*it);
			}
			for(i = 0, size = _ghosts.size(); i < size; i++)
				delete _ghosts[i];
		}
		void stopPacman();
		void pacmanSetDirection(int i);
		void createBalls();
		void drawPoints();	
		void draw(bool help);
		bool moves(char key, char p2key, long unsigned int t);
		void changeState();	
		Pacman *getPacman() { return _pacman; }
		Camera *getCamera() { return _camera; }
		ScoreBoard *scoreBoard() { return _scoreBoard; }
		void setCamera(Camera *cam) { delete _camera; _camera = cam; }
		void setLight(Light *light) { delete _light; _light = light; _light->enable(); }
		static void panicModeOff(int value);
		void floorTexture() { _board->texture(); }
		void colision(int i);
		void ballEaten();
		
};

#endif
