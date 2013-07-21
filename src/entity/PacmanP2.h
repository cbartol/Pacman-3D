#ifndef __PACMANP2_H__
#define __PACMANP2_H__

#include "Pacman.h"
#include "../conventions.h"
#define pac_radius 0.5

class PacmanP2: virtual public Pacman{
	public:
		PacmanP2(float x, float y): Pacman(x,y){}
		~PacmanP2(){}
		void draw(bool gameOver, bool gameWin);
	private:
		void pacEyes();		
		void pacEyebrows();
		void pacMouth();	
		void pacBody();
		
};
#endif
