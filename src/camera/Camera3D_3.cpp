#include "Camera3D_3.h"
#include "../Game.h"

Camera3D_3::Camera3D_3(Game *g) {
	int direction = g->getPacman()->getDirection();

	_camPos = g->getPacman()->getPos();
	if(direction == UP){
		_camDest.x = _camPos.x;
		_camDest.y = _camPos.y + 5;
	} else if(direction == DOWN){
		_camDest.x = _camPos.x;
		_camDest.y = _camPos.y - 5;
	} else if(direction == LEFT){
		_camDest.x = _camPos.x - 5;
		_camDest.y = _camPos.y;
	} else if(direction == RIGHT){
		_camDest.x = _camPos.x + 5;
		_camDest.y = _camPos.y;
	}
	_camDest.z = _camPos.z;
	
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

void Camera3D_3::update(Game *g, long unsigned int dt){
	int direction = g->getPacman()->getDirection();
	
	_camPos = g->getPacman()->getPos();
	if(direction == UP){
		_camDest.x = _camPos.x;
		_camDest.y = _camPos.y + 5;
	} else if(direction == DOWN){
		_camDest.x = _camPos.x;
		_camDest.y = _camPos.y - 5;
	} else if(direction == LEFT){
		_camDest.x = _camPos.x - 5;
		_camDest.y = _camPos.y;
	} else if(direction == RIGHT){
		_camDest.x = _camPos.x + 5;
		_camDest.y = _camPos.y;
	}
		_camDest.z = _camPos.z;
}

void Camera3D_3::setCamera(){
	gluLookAt(_camPos.x, _camPos.y, _camPos.z, _camDest.x, _camDest.y, _camDest.z, 0, 0, 1);
}

void Camera3D_3::setProjectionMode(double width, double height){
	gluPerspective(70, width / (height * 1.0), 0.49999, 30);
}
char Camera3D_3::convertDirection(Game *g, char dir){
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
