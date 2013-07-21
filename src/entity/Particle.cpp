#include "Particle.h"

void Particle::draw(){
	if(_isDead)	return;
	GLfloat body_Ka[] = { 0. , 0. , 0., 1.};
	GLfloat body_Kd[] = { _color.x , _color.y , _color.z, 1.};
	GLfloat body_Ks[] = { 0.63 , 0.56 , 0.37, 1.};
	GLfloat body_Ke[] = { 0.0 , 0.0 , 0.0, 1.};

	giveMaterialColor(body_Ka, body_Kd, body_Ks, body_Ke, 96.);
	glPushMatrix();
		glTranslatef(_actual.x, _actual.y,_actual.z);
		glutSolidSphere(_size, 6, 6);
	glPopMatrix();
}


void Particle::update(long unsigned int dt){
	if(_actual.z <= -0.5)
		_lifetime -= dt;
	if(_lifetime <= 0)
		_isDead=true;
		
	if(_actual.z <= -0.5 && (_actual.x >= -12 && _actual.x <= 12) && (_actual.y >= -7 && _actual.y <= 7)){
		_actual.z=-0.5;
	}else{
		_actual.x += _speed.x * dt + _ac.x * (dt * dt); 
		_actual.y += _speed.y * dt + _ac.y * (dt * dt);
		_actual.z += _speed.z * dt + _ac.z * (dt * dt);
		_speed.z += _ac.z * dt;
	}
}

void Particle::reset(position pac){
	_isDead=false;
	_actual= pac;
	_lifetime = 2000;
	_speed.z = ((rand() % 100) + 50.)/20000.;
}
