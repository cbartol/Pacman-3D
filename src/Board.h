#ifndef __BOARD_H__
#define __BOARD_H__

#include "conventions.h"
#include "Ball.h"
#include <string>

class Game;
class Board {
	private:
		Ball* _ballsArray[15][25];
		int _boardArray[15][25];
		const unsigned char* _image;
		int _iheight, _iwidth;

	public:
		Board();
		~Board(){
		}
		void draw();
		position checkPacmanPath(position orig, position dest, char key, int *dir, Game* game);
		position checkGhostPath(position orig, position dest, char key, int *dir, Game* game);
		void addBall(float x, float y, Ball * b);
		void texture();
		bool checkColision(position pos1, position pos2); 
	private:
		
		void draw_floor_texture();
		void drawfloor();
		void drawWall(float tx, float ty, float sx, float sy, bool xxSimetric, bool yySimetric);
};
#endif
