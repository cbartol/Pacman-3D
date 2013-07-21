extern "C" {
	#include "extralib/glm.h"
}

#include "Board.h"
#include "Game.h"
#include "conventions.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
void fillBoardArray(int array[15][25]);
Board::Board(){
	char file[] = "grass.ppm";
	_image = glmReadPPM(file, &_iwidth, &_iheight);
	for(int i = 0; i< 15 ; i++){
		for(int j = 0; j< 25 ; j++){
			_ballsArray[i][j] = NULL;
		}
	}
	fillBoardArray(_boardArray);
}

void Board::addBall(float x, float y, Ball * b){
	int xx = x + 12, yy = (-y)+  7;
	_ballsArray[yy][xx] = b;
}


void Board::draw(){
	drawfloor();
	
/****FRONTEIRA****/
	drawWall(-12., 7., 25., 1., false, true);
	drawWall(12., -7., 1., 15., true, false);

/****INTERIOR****/
/*CUBO(2x2)_CANTOS*/
	drawWall(9.,4., 2.,2., true, true);
/*PARALELEPIPEDO(1x5)_LATERAIS*/
	drawWall(-10.,-2., 1.,5., true, false);
/*PARALELEPIPEDO(1x2)_FRONTEIRA*/
	drawWall(5.,5., 1.,2., true, true);
/*PARALELEPIPEDO(2x3)_CENTRO*/
	drawWall(-5.,-1., 2.,3., true, false);
/*PARALELEPIPEDO(3x1)_TOPCENTRO*/
	drawWall(-1.,3., 3.,1., false, true);
/**CONJUNTOS**/
/**<<1>>**/
/*CUBO(2x2)*/
	drawWall(7.,1., 2.,2., true, true);
/*PARALELEPIPEDO(2x1)*/	
	drawWall(5.,3., 2.,1., true, true);
/*PARALELEPIPEDO(1x3)*/	
	drawWall(7.,3., 1.,3., true, true);
/**<<2*>>**/
/*PARALELEPIPEDO(7x1)*/	
	drawWall(-3.,5., 7.,1., false, true);
/*PARALELEPIPEDO(1x2)*/	
	drawWall(3.,3., 1.,2., true, true);
/**<<3>>**/
/*PARALELEPIPEDO(5x1)*/	
	drawWall(-2.,1., 5.,1., false, true);


/*PORTA DOS FANTASMAS*/
	glColor3f(0.4,0.,0.);
	GLfloat wall_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat wall_Kd[] = { .61 , .33 , .18, 1.};
	GLfloat wall_Ks[] = { 0. , 0. , 0., 1.};
	GLfloat wall_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

	giveMaterialColor(wall_Ka, wall_Kd, wall_Ks, wall_Ke, 5.);
	glPushMatrix();
		glTranslatef(2.4,0., -.25);
		glScalef(0.2, 1., 0.5);
		glutSolidCube(1.);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2.4,0., -.25);
		glScalef(0.2, 1., 0.5);
		glutSolidCube(1.);
	glPopMatrix();
}

void Board::drawWall(float tx, float ty, float sx, float sy, bool xxSimetric, bool yySimetric){
	GLfloat wall_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat wall_Kd[] = { .0 , .22 , .0, 1.};
	GLfloat wall_Ks[] = { 0. , 0. , 0., 1.};
	GLfloat wall_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

	giveMaterialColor(wall_Ka, wall_Kd, wall_Ks, wall_Ke, 5.);
	glColor3f(0.0,0.1,0.2);
	
	glPushMatrix();
		glTranslatef(0,0,-0.25);
		glScalef(1,1,0.5);
		for(float i = 0.; i < sx; i++){
			for(float j = 0.; j < sy; j++){
				glPushMatrix();
						glTranslatef(tx+i,ty+j, -.2);
						glutSolidCube(1.);
				glPopMatrix();
				if(xxSimetric){
					glPushMatrix();
						glTranslatef(-tx-i,ty+j, -.2);
						glutSolidCube(1.);
					glPopMatrix();
				}
				if(yySimetric){
					glPushMatrix();
						glTranslatef(tx+i,-ty-j, -.2);
						glutSolidCube(1.);
					glPopMatrix();
				}
				if(xxSimetric && yySimetric){
					glPushMatrix();
						glTranslatef(-tx-i,-ty-j, -.2);
						glutSolidCube(1.);
					glPopMatrix();
				}
			}
		}
	glPopMatrix();
}


void Board::drawfloor(){
	GLfloat floor_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat floor_Kd[] = { .8 , .8 , .8, 1.};
	GLfloat floor_Ks[] = { 0. , 0. , 0., 1.};
	GLfloat floor_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

	giveMaterialColor(floor_Ka, floor_Kd, floor_Ks, floor_Ke, 5.);
		
	draw_floor_texture();
}

void fillBoardArray(int array[15][25]){
	int board[15][25] ={{ W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
		                      { W,B,B,B,B,B,B,W,B,B,B,B,B,B,B,B,B,W,B,B,B,B,B,B,W},
		                      { W,B,W,W,B,W,B,W,B,W,W,W,W,W,W,W,B,W,B,W,B,W,W,B,W},
		                      { W,B,W,W,B,W,B,B,B,W,B,B,B,B,B,W,B,B,B,W,B,W,W,B,W},
		                      { W,B,B,B,B,W,W,W,B,W,B,W,W,W,B,W,B,W,W,W,B,B,B,B,W},
		                      { W,B,W,B,W,W,B,B,B,B,B,B,E,B,B,B,B,B,B,W,W,B,W,B,W},
		                      { W,B,W,B,W,W,B,W,W,B,W,W,W,W,W,B,W,W,B,W,W,B,W,B,W},
		                      { W,B,W,B,B,B,B,W,W,B,E,E,E,E,E,B,W,W,B,B,B,B,W,B,W},
		                      { W,B,W,B,W,W,B,W,W,B,W,W,W,W,W,B,W,W,B,W,W,B,W,B,W},
		                      { W,B,W,B,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,W,W,B,W,B,W},
		                      { W,B,B,B,B,W,W,W,B,W,B,W,W,W,B,W,B,W,W,W,B,B,B,B,W},
		                      { W,B,W,W,B,W,B,B,B,W,B,B,B,B,B,W,B,B,B,W,B,W,W,B,W},
		                      { W,B,W,W,B,W,B,W,B,W,W,W,W,W,W,W,B,W,B,W,B,W,W,B,W},
		                      { W,B,B,B,B,B,B,W,B,B,B,B,B,B,B,B,B,W,B,B,B,B,B,B,W},
		                      { W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}};

	for(int i = 0; i < 15 ; i++){
		for(int j = 0; j < 25 ; j++){
			array[i][j] = board[i][j];
		}
	}
}
