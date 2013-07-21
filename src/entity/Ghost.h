#ifndef __GHOST_H__
#define __GHOST_H__
#include "../conventions.h"
#include <vector>

class Ghost{
	private:
		float _xcoord;
		float _ycoord;
		float _lookAngle; // angulo para ficar virado para o pacman;
		float _color[3];
		bool _eatable;
		bool _up, _down, _left, _right;
		position _leftEye;
		position _rightEye;
		position _leftEyebrows;
		position _rightEyebrows;
		std::vector<position> _bodyVertex;
		std::vector<position> _bodyNormals;

	public:
		Ghost(float x , float y, position pacPos, float cor[3]);
		~Ghost(){}
		void draw();
		void lookToPacman(position pacPos);
		void setState(){_eatable = true;}
		void unsetState(){_eatable = false;}
		bool isEatable() {return _eatable;}
		void setDirection(int dir);		
		void move(position dest);
		position premove(long unsigned int dt, position pacPos, char *dir);
		bool isDirectionSet();
		int getDirection();
		position getPos(){ return position(_xcoord, _ycoord, 0);}
		void die();
	private:
		void ghostEyes();
		void ghostEyebrows();
		void ghostMouth();
		void ghostBody();
		void reset();
		static void replacing(int value);
};
#endif
