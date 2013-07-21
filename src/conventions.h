#ifndef __CONVENTIONS_H__
#define __CONVENTIONS_H__

#ifndef MULTI_PLAYER
	#define MULTI_PLAYER false
#endif

#include <cmath>
#include <GL/glut.h>
#define frand()			((float)rand()/RAND_MAX)
#define PI 3.1415926535897932384626433832795028841971693993751058
#define XX(r,t,f) r*cos(t)*sin(f)
#define YY(r,t,f) r*sin(t)*sin(f)
#define ZZ(r,t,f) r*cos(f)

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define W 0
#define B 1
#define G 2
#define E 3


typedef struct _pos{
	float x;
	float y;
	float z;
	_pos(float xx = 0, float yy = 0, float zz = 0) : x(xx), y(yy), z(zz) { } 
} position;

inline float ANGLEV(float ux, float uy, float vx, float vy){
	return acos((ux*vx + uy*vy)/(sqrt(pow(ux,2.)+pow(uy,2.))*sqrt(pow(vx,2.)+pow(vy,2.))));
}

inline void giveMaterialColor(GLfloat ka[4], GLfloat kd[4], GLfloat ks[4], GLfloat ke[4], GLfloat shininess){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
	glMaterialfv(GL_FRONT, GL_EMISSION, ke);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


#endif
