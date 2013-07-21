#include "Ghost.h"
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#define ghost_radius 0.5
#define N_FACES 8.0

Ghost::Ghost(float x , float y, position pacPos, float cor[3]): _xcoord(x), _ycoord(y), _up(false), _down(true), _left(false), _right(false),
						_leftEye(XX(ghost_radius, 3.*PI/4., PI/4.),YY(ghost_radius, 3.*PI/4., PI/4.),ZZ(ghost_radius, 3.*PI/4., -PI/4.)),
						_rightEye(XX(ghost_radius, PI/4., PI/4.),YY(ghost_radius, PI/4., PI/4.),ZZ(ghost_radius, PI/4., PI/4.)),
						_leftEyebrows(XX(ghost_radius, 3.*PI/5., PI/3.),YY(ghost_radius, 3.*PI/5., PI/3.),ZZ(ghost_radius, 3.*PI/5., PI/3.)+0.1),
						_rightEyebrows(XX(ghost_radius, 2.*PI/5., PI/3.),YY(ghost_radius, 2.*PI/5., PI/3.),ZZ(ghost_radius, 2.*PI/5., PI/3.)+0.1)
{
	lookToPacman(pacPos);
	for(int i = 0 ; i < 3 ; i++){
		_color[i] = cor[i];
	}
	_eatable = false;

	const double ang1 = 2.*PI/N_FACES;
	double z0, z1, x0, x1, n0, n1, n, c;

	for(double ang = 0; ang < 2.*PI ; ang += ang1){
		z0 = ghost_radius * sin(ang);
		x0 = ghost_radius * cos(ang);
		z1 = ghost_radius * sin(ang+ang1);
		x1 = ghost_radius * cos(ang+ang1);
		
		n0 = sqrt(x0*x0+z0*z0);		
		n1 = sqrt(x1*x1+z1*z1);
		n = sqrt(ghost_radius * cos(ang+(ang1/2.))*ghost_radius * cos(ang+(ang1/2.)) +ghost_radius * sin(ang+(ang1/2.))*ghost_radius * sin(ang+(ang1/2.)));

		/* Parte Superior_(Triângulo) da face */
		_bodyVertex.push_back(position(0.,.9,0.)); 			// 0
		_bodyNormals.push_back(position(0., 1., 0.));

		_bodyVertex.push_back(position(x1 , 0.4, z1));			// 10
		_bodyNormals.push_back(position(x1/(sqrt(x1*x1+z1*z1)), 0., z1/(sqrt(x1*x1+z1*z1))));

		_bodyVertex.push_back(position(x0 , 0.4, z0)); 			// 2
		_bodyNormals.push_back(position(x0/(sqrt(x0*x0+z0*z0)), 0., z0/(sqrt(x0*x0+z0*z0))));
		
		/* Parte Inferior da face */
		_bodyVertex.push_back(position(x0,.4, z0)); 			// 3
		_bodyNormals.push_back(position(x0/(sqrt(x0*x0+z0*z0)), 0., z0/(sqrt(x0*x0+z0*z0))));

		_bodyVertex.push_back(position(x1,.4, z1)); 			// 9
		_bodyNormals.push_back(position(x1/(sqrt(x1*x1+z1*z1)), 0., z1/(sqrt(x1*x1+z1*z1))));

		_bodyVertex.push_back(position(x1,.0, z1)); 			// 8.4
		_bodyNormals.push_back(position(x1/n1, 0., z1/n1));

		_bodyVertex.push_back(position(x1,-.3, z1)); 			// 8
		_bodyNormals.push_back(position(x1/n1, 0., z1/n1));
		
		_bodyVertex.push_back(position(ghost_radius * cos(ang+(ang1/2.)),-.5, ghost_radius * sin(ang+(ang1/2.)))); 	// 6
		_bodyNormals.push_back(position((ghost_radius * cos(ang+(ang1/2.)))/n, 0., (ghost_radius * sin(ang+(ang1/2.)))/n));

		_bodyVertex.push_back(position(x0,-.3, z0)); 									// 4
		_bodyNormals.push_back(position(x0/n0, 0., z0/n0));


		_bodyVertex.push_back(position(x0,0., z0)); 									// 4.2
		_bodyNormals.push_back(position(x0/n0, 0., z0/n0));
	}
}

void Ghost::draw(){
	float anglePacYY;
	glPushMatrix();
		glTranslatef(_xcoord, _ycoord,0.);
		glRotatef(_lookAngle, 0., 0., 1.);	//Rotação em torno do eixo z, para Fantasma ficar virado para Pacman
		glRotatef(90., 1., 0., 0.);		//Fantasma é desenhado virado no sentido positivo	
		ghostBody();				//do eixo z, logo é necessária uma rotação de 90º
		ghostEyes();				//em torno do eixo x
		ghostEyebrows();
//		ghostMouth();	
	glPopMatrix();
}

void Ghost::lookToPacman(position pacPos){
	_lookAngle = atan2((pacPos.x - _xcoord),-(pacPos.y - _ycoord))*180.0/PI;
}

inline void Ghost::ghostEyes(){
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
inline void Ghost::ghostEyebrows(){
	GLfloat eyebrown_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat eyebrown_Kd[] = { .6 , .6 , 0.6, 1.};
	GLfloat eyebrown_Ks[] = { 0. , 0. , 0., 1.};
	GLfloat eyebrown_Ke[] = { 0.0 , 0.0 , 0.0, 1.};
	giveMaterialColor(eyebrown_Ka, eyebrown_Kd, eyebrown_Ks, eyebrown_Ke, 10.);
	glColor3f(0.6,0.6,0.6);
/* sobrancelha direita */
	glPushMatrix();
		glTranslatef(_rightEyebrows.x, _rightEyebrows.y, _rightEyebrows.z);
		glRotatef(20,0.0,0.0, 1.0);
		glScalef(2.5, 0.5, .5);
		glutSolidSphere(0.1, 8,8);
	glPopMatrix();
	
/* sobrancelha esquerda */
	glPushMatrix();
		glTranslatef(_leftEyebrows.x, _leftEyebrows.y, _leftEyebrows.z);
		glRotatef(-20,0.0,0.0, 1.0);
		glScalef(2.5, 0.5, .5);
		glutSolidSphere(0.1, 8,8);
	glPopMatrix();
}
void Ghost::ghostMouth(){
}
inline void Ghost::ghostBody(){
	GLfloat body_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat body_Kd[] = { _color[0] , _color[1] , _color[2], .55};
	GLfloat body_Ks[] = { 0.63 , 0.63 , 0.63, .55};
	GLfloat body_Ke[] = { 0.0 , 0.0 , 0.0, 1.};
	
	GLfloat whiteBody_Kd[] = { 1. , 1. , 1., .55};

	const int size = _bodyVertex.size();
	if(_eatable){				// Se for "comestivel"
		glColor3f(1., 1., 1.);
		giveMaterialColor(body_Ka, whiteBody_Kd, body_Ks, body_Ke, 77.);	// Material branco
	} else {
		giveMaterialColor(body_Ka, body_Kd, body_Ks, body_Ke, 77.);			// Material normal
		glColor3f(_color[0],_color[1], _color[2]);
	}
	glPushMatrix();
		for(int i = 0; i < size ; i++){
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
				i++;
				glNormal3f(_bodyNormals[i].x, _bodyNormals[i].y, _bodyNormals[i].z);
				glVertex3f(_bodyVertex[i].x, _bodyVertex[i].y, _bodyVertex[i].z);
			glEnd();
		}
	glPopMatrix();
}



bool Ghost::isDirectionSet(){
	return (_up || _down || _left || _right);
}

void Ghost::setDirection(int dir){
	_up = _down = _left = _right = false;
	if(dir == UP)
		_up = true;
	else if(dir == DOWN)
		_down = true;
	else if(dir == LEFT)
		_left = true;
	else if(dir == RIGHT)
		_right = true;
}
void Ghost::move(position dest){
	_xcoord = dest.x;
	_ycoord = dest.y;
	return;
}

position Ghost::premove(long unsigned int dt, position pacPos, char *dir){ //throw IOException ?!?!?!?!?!
	float x, y;
	double deslocamento;
	x = pacPos.x - _xcoord;		// Diferença entre as coordenadas do Pacman e do Ghost, no eixo dos xx
	y = pacPos.y - _ycoord;		// Diferença entre as coordenadas do Pacman e do Ghost, no eixo dos yy
	*dir = 0;
	
	if(_eatable){					// Se o Ghost estiver no estado especial
		if(fabs(x) > fabs(y)){		//Contrário ao estado normal
			if( x > 0.)
				*dir = 'a';
			else if(x < 0.)
				*dir = 'd';
		} else{
			if( y > 0.)
				*dir = 's';
			else if(y < 0.)
				*dir = 'w';
		}				// Velocidade passa a 2/3 da velocidade do Pacman
		deslocamento = dt * .003f * (2./3.);
	} else {					// Se o Ghost estiver no estado normal
		if(fabs(x) > fabs(y)){		// Se a diferença no eixo dos xx for maior e
			if( x < 0.)		// Negativa, o Ghost vai querer andar para a ESUERDA
				*dir = 'a';
			else if(x > 0.)		// Positiva, o Ghost vai querer andar para a Direita
				*dir = 'd';
		} else{				// Caso contrário,
			if( y < 0.)		// Negativa, o Ghost vai querer andar para a BAIXO
				*dir = 's';
			else if(y > 0.)		// Positiva, o Ghost vai querer andar para a CIMA
				*dir = 'w';
		}
		deslocamento = dt * .003f;
	}

	position dest = position(_xcoord, _ycoord);	//Posição final da simulação
	if(_up)
		((_ycoord + deslocamento > 7) ? (dest = position(_xcoord, 7)):(dest = position(_xcoord, _ycoord + deslocamento)));
	else if(_down)
		((_ycoord - deslocamento < -7) ? (dest = position(_xcoord, -7)):(dest = position(_xcoord, _ycoord - deslocamento)));
	else if(_left)
		((_xcoord - deslocamento < -12) ? (dest = position(-12, _ycoord)):(dest = position(_xcoord - deslocamento, _ycoord)));
	else if(_right)
		((_xcoord + deslocamento > 12) ? (dest = position(12, _ycoord)):(dest = position(_xcoord + deslocamento, _ycoord)));
	return  dest;
}


int Ghost::getDirection(){
	if(_up)
		return UP;
	else if(_down)
		return DOWN;
	else if(_left)
		return LEFT;
	else if(_right)
		return RIGHT;
	else
		return 0;
}


void Ghost::die(){	
	unsetState();
	_xcoord= 100;
	_ycoord= 100;
	 _up= _down= _left= _right= false;
	glutTimerFunc(5000, Ghost::replacing, reinterpret_cast<long int> (this));	
}

void Ghost::replacing(int value){
	Ghost * g = reinterpret_cast<Ghost *> (value);
	g->_xcoord= g->_ycoord= 0;
	g->_left=true;
}
