#include "Pacman.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>

bool Pacman::isDirectionSet(){
	return (_up || _down || _left || _right);
}

void Pacman::setDirection(int dir){
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

void Pacman::stop(){
	_up = _down = _left = _right = false;
}

void Pacman::move(position dest){
	_xcoord = dest.x;
	_ycoord = dest.y;
	return;
}

position Pacman::premove(long unsigned int dt){
	double deslocamento = dt * .003f;
	position dest = position(_xcoord, _ycoord);	//Posição final da simulação
	if(_isDead){
		explosion(dt);
		return dest;
	}
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


int Pacman::getDirection(){
	if(_isDead)
		return 0;
	else if(_up)
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


void Pacman::bang(){
	if(_isDead)
		return;
	_isDead = true;
	int size = _particles.size();
	glutTimerFunc(7000, Pacman::replacing, reinterpret_cast<long int> (this));	
	for(int i=0; i < size; i++)
		_particles[i]->reset(getPos());
   	_xcoord = 0;
	_ycoord = -12;
}

void Pacman::explosion(long unsigned int dt){
	int size = _particles.size();
	for(int i=0; i < size; i++)
		_particles[i]->update(dt);
}

void Pacman::replacing(int value){
	Pacman * p = reinterpret_cast<Pacman *> (value);
	p->_xcoord = 0;
	p->_ycoord = 2;
	p->setDirection(DOWN);
	p->_isDead=false;
}
