#ifndef __PACMANP1_H__
#define __PACMANP1_H__

#include "Pacman.h"
#include "../conventions.h"
#define pac_radius 0.5

class PacmanP1: virtual public Pacman{

	public:
		PacmanP1(float x, float y): Pacman(x,y){}
		~PacmanP1(){}
		void draw(bool gameOver, bool gameWin);
	private:
		void pacEyes();		
		void pacEyebrows();
		void pacMouth();	
		void pacBody();
		
};
#endif
