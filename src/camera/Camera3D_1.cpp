#include "Camera3D_1.h"
#include "../Game.h"

Camera3D_1::Camera3D_1(Game *g) {
	_camDest = g->getPacman()->getPos();
	_camPos.x = _camDest.x;
	_camPos.y = _camDest.y - 7.5;
	_camPos.z = _camDest.z + 7.5;
}
		
void Camera3D_1::update(Game *g, long unsigned int dt){
	_camDest = g->getPacman()->getPos();
	_camPos.x = _camDest.x;
	_camPos.y = _camDest.y - 7.5;
	_camPos.z = _camDest.z + 7.5;
}

void Camera3D_1::setCamera(){
	gluLookAt(_camPos.x, _camPos.y, _camPos.z, _camDest.x, _camDest.y, _camDest.z, 0, 0, 1);
}

void Camera3D_1::setProjectionMode(double width, double height){
	gluPerspective(45, width / (height * 1.0), 1, 30);
}

char Camera3D_1::convertDirection(Game *g, char dir){
	return dir;
}
