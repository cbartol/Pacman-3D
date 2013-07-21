#include "PacmanP1.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>

void PacmanP1::draw(bool gameOver, bool gameWin){
	if(!_isDead){
		if(gameOver && !gameWin) return;
		glPushMatrix();
			glTranslatef(_xcoord, _ycoord,0.);
			if(_up){
				glRotatef(180., 0., 0., 1.);
				glRotatef(90., 1., 0., 0.);
			}
			else if(_down){
				glRotatef(90., 1., 0., 0.);
			}
			else if(_left){
				glRotatef(-90., 0., 0., 1.);
				glRotatef(90., 1., 0., 0.);
			}
			else if(_right){
				glRotatef(90., 0., 0., 1.);
				glRotatef(90., 1., 0., 0.);
			}
			else {
				glRotatef(50., 1., 0., 0.);
			}
			pacBody();
			pacEyes();
			pacEyebrows();
			pacMouth();
		
		glPopMatrix();
	}else {
		int size = _particles.size();
		for(int i=0; i < size; i++)
			_particles[i]->draw();
	
	}	
}

inline void PacmanP1::pacEyes(){ 
	GLfloat eyeb_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat eyeb_Kd[] = { .0 , .0 , 0.0, 1.};
	GLfloat eyeb_Ks[] = { 0. , 0. , 0., 1.};
	GLfloat eyeb_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

	GLfloat eyew_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat eyew_Kd[] = { 1.0 , 1.0 , 1.0, 1.};
	GLfloat eyew_Ks[] = { 0.4 , 0.4 , 0.4, 1.};
	GLfloat eyew_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

/* olho direito */
	glPushMatrix();
		glTranslatef(_rightEye.x, _rightEye.y, _rightEye.z);
		glColor3f(1.,1.,1.);
		giveMaterialColor(eyew_Ka, eyew_Kd, eyew_Ks, eyew_Ke, 96.);
		glutSolidSphere(0.2, 6,6);
		glColor3f(0.,0.,0.);
		giveMaterialColor(eyeb_Ka, eyeb_Kd, eyeb_Ks, eyeb_Ke, 10.);
		glTranslatef(0.,0.,0.15);
		glutSolidSphere(0.1, 6,6); 
	glPopMatrix();

/* olho esquerdo */
	glPushMatrix();
		glTranslatef(_leftEye.x, _leftEye.y, _leftEye.z);
		glColor3f(1.,1.,1.);
		giveMaterialColor(eyew_Ka, eyew_Kd, eyew_Ks, eyew_Ke, 96.);
		glutSolidSphere(0.2, 6,6);
		glColor3f(0.,0.,0.);
		giveMaterialColor(eyeb_Ka, eyeb_Kd, eyeb_Ks, eyeb_Ke, 10.);
		glTranslatef(0.,0.,0.15);
		glutSolidSphere(0.1, 6,6); 
	glPopMatrix();
}

inline void PacmanP1::pacEyebrows(){
	GLfloat eyebrown_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat eyebrown_Kd[] = { .0 , .0 , 0.0, 1.};
	GLfloat eyebrown_Ks[] = { 0. , 0. , 0., 1.};
	GLfloat eyebrown_Ke[] = { 0.0 , 0.0 , 0.0, 1.};
	giveMaterialColor(eyebrown_Ka, eyebrown_Kd, eyebrown_Ks, eyebrown_Ke, 10.);
/* sobrancelha direita */
	glPushMatrix();
		glTranslatef(_rightEyebrows.x, _rightEyebrows.y, _rightEyebrows.z);
		glRotatef(20,0.0,0.0, 1.0);
		glScalef(2.5, 0.5, .5);
		glColor3f(0.,0.,0.);
		glutSolidSphere(0.1, 6,6);
	glPopMatrix();
	
/* sobrancelha esquerda */
	glPushMatrix();
		glTranslatef(_leftEyebrows.x, _leftEyebrows.y, _leftEyebrows.z);
		glRotatef(-20,0.0,0.0, 1.0);
		glScalef(2.5, 0.5, .5);
		glColor3f(0.,0.,0.);
		glutSolidSphere(0.1, 6,6);
	glPopMatrix();
}

inline void PacmanP1::pacMouth(){
/*
	glPushMatrix();
		glTranslatef(XX(pac_radius, -PI/2., PI/8.), YY(pac_radius, -PI/2., PI/8.), ZZ(pac_radius, -PI/2., PI/8.));
		glScalef(2., 0.5, .1);
		glColor3f(0.5,0.,0.);
		glutSolidSphere(0.2, 8,8);
	glPopMatrix();
*/
}

void PacmanP1::pacBody(){
	GLfloat body_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat body_Kd[] = { 1.0 , 1.0 , 0.0, 1.};
	GLfloat body_Ks[] = { 0.63 , 0.56 , 0.37, 1.};
	GLfloat body_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

	giveMaterialColor(body_Ka, body_Kd, body_Ks, body_Ke, 96.);

	glPushMatrix();
		glColor3f(1.,1.,0.);
		glutSolidSphere(pac_radius, 25,25);
	glPopMatrix();
}
