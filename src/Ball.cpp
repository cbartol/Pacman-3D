#include "Ball.h"
#include <GL/glut.h>

void Ball::draw(){
	GLfloat ball_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat ball_Kd[] = { 1 , 1 , 1, 1.};
	GLfloat ball_Ks[] = { 0.77 , 0.46 , 0.20, 1.};
	GLfloat ball_Ke[] = { 0.0 , 0.0 , 0.0, 0.};
	
	GLfloat sball_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat sball_Kd[] = { .08 , .61 , 0.08, .55};
	GLfloat sball_Ks[] = { .63 , 0.73 , 0.63, .55};
	GLfloat sball_Ke[] = { 0.0 , 0.0 , 0.0, 0.};
	if(_eaten)
		return;
	if(_special){
		glPushMatrix();
			glTranslatef(Ball::_pos.x, Ball::_pos.y, Ball::_pos.z);
			glColor3f(.6, .6, .0);
			giveMaterialColor(sball_Ka, sball_Kd, sball_Ks, sball_Ke, 100.);
			glutSolidSphere(0.25, 20, 20);
		glPopMatrix();
	} else {
		glPushMatrix();
			glTranslatef(_pos.x, _pos.y, _pos.z);
			glColor3f(.9, .2, .0);
			giveMaterialColor(ball_Ka, ball_Kd, ball_Ks, ball_Ke, 128.);
			glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
}

int Ball::eaten(){
	_eaten = true;
	return _points;
}

bool Ball::wasEaten(){
	return _eaten;
}

bool Ball::isSpecial(){
	return _special;
}
