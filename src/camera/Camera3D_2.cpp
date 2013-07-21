#include "Camera3D_2.h"
#include "../Game.h"

Camera3D_2::Camera3D_2(Game *g) {
	int direction = g->getPacman()->getDirection();
	
	_camDest = g->getPacman()->getPos();
	if(direction == UP){
		_camPos.x = _camDest.x;
		_camPos.y = _camDest.y - 5;
	} else if(direction == DOWN){
		_camPos.x = _camDest.x;
		_camPos.y = _camDest.y + 5;
	} else if(direction == LEFT){
		_camPos.x = _camDest.x + 5;
		_camPos.y = _camDest.y;
	} else if(direction == RIGHT){
		_camPos.x = _camDest.x - 5;
		_camPos.y = _camDest.y;
	}
	_camPos.z = _camDest.z + 5;
	_camDest.z += 2;
		
	//Conversão das Teclas
	_up['a'] = 'a';
	_up['w'] = 'w';
	_up['s'] = 's';
	_up['d'] = 'd';

	_down['a'] = 'd';
	_down['w'] = 's';
	_down['s'] = 'w';
	_down['d'] = 'a';

	_left['a'] = 's';
	_left['w'] = 'a';
	_left['s'] = 'd';
	_left['d'] = 'w';

	_right['a'] = 'w';
	_right['w'] = 'd';
	_right['s'] = 'a';
	_right['d'] = 's';
}

void Camera3D_2::update(Game *g, long unsigned int dt){
	int direction = g->getPacman()->getDirection();
	
	_camDest = g->getPacman()->getPos();
	if(direction == UP){
		_camPos.x = _camDest.x;
		_camPos.y = _camDest.y - 5;
	} else if(direction == DOWN){
		_camPos.x = _camDest.x;
		_camPos.y = _camDest.y + 5;
	} else if(direction == LEFT){
		_camPos.x = _camDest.x + 5;
		_camPos.y = _camDest.y;
	} else if(direction == RIGHT){
		_camPos.x = _camDest.x - 5;
		_camPos.y = _camDest.y;
	}
	_camPos.z = _camDest.z + 5;
	_camDest.z += 2;
}

void Camera3D_2::setCamera(){
	gluLookAt(_camPos.x, _camPos.y, _camPos.z, _camDest.x, _camDest.y, _camDest.z, 0, 0, 1);
}

void Camera3D_2::setProjectionMode(double width, double height){
	gluPerspective(45, width / (height * 1.0), 1, 30);
}
char Camera3D_2::convertDirection(Game *g, char dir){
	if(dir != 'a' && dir != 'w' && dir != 's' && dir != 'd')
		return dir;
	int direction = g->getPacman()->getDirection();
	if(direction == UP){
		return _up[dir];
	} else if(direction == DOWN){
		return _down[dir];
	} else if(direction == LEFT){
		return _left[dir];
	} else if(direction == RIGHT){
		return _right[dir];
	}
	return dir;
}
