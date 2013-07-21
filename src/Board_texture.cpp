#include "Board.h"
#include <iostream>

void Board::texture(void){
	//texenv()
	GLfloat border_color[] = {1.0, 1. , 1. , 1.};
	GLfloat env_color[] = {1. , 1. , 1. , 1.};
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, env_color);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
	
	//----------------
//	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _iwidth, _iheight, GL_RGB, GL_UNSIGNED_BYTE, _image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _iwidth, _iheight, 0,GL_RGB, GL_UNSIGNED_BYTE, _image);
}

void Board::draw_floor_texture(){
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.,1.,1.);
	for(float i = -12.; i < 12.; i++){
		for(float j = -7.; j < 7.; j++){
			glBegin(GL_POLYGON);
				glNormal3f(0., 0., 1.);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(i, j, -.5);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(i+1., j, -.5);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(i+1., j+1., -.5);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(i, j+1., -.5);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
}
