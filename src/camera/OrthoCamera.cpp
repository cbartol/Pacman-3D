#include "OrthoCamera.h"
#include "../Game.h"

void OrthoCamera::update(Game *g, long unsigned int dt){}

void OrthoCamera::setCamera(){}

void OrthoCamera::setProjectionMode(double width, double height){
	double ratio = (width / (height*(13./8.)));

	if ( ratio >= 1. )
		glOrtho(-13.0f*ratio, 13.0f*ratio, -8.0f, 8.0f, -2.0f, 2.0f);
	else
		glOrtho(-13.0f, 13.0f, -8.0f/ratio, 8.0f/ratio, -2.0f, 2.0f);
}

char OrthoCamera::convertDirection(Game *g, char dir){
	return dir;
}
