#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "../conventions.h"
#include <GL/glut.h>
#include <stdlib.h>
typedef position speed;
typedef position aceleration;
typedef position color;

class Particle{
	protected:
		position _actual;
		speed _speed;
		aceleration _ac;
		color _color;
		float _size;
		bool _isDead;
		long int _lifetime;

	public:
		Particle() : _isDead(true), _lifetime(2000){
			float x, y, z, v, phi, theta;
			v = 0.01*frand();
			phi = frand()*PI;
			theta = 2.0*frand()*PI;
			_speed.x = v * cos(theta) * sin(phi)  *0.4;
			_speed.y = v * sin(theta) * sin(phi) *0.4;
			_speed.z = v * cos(phi)*1.5;
		   _ac.x =  0.00f; 
			_ac.y =  0.0f;
			_ac.z = -5e-6;
			_size = ((rand() % 9) + 1.)/100.;
			if((rand() % 100) < 95)
				_color = color(.8, (rand() % 2)*0.8, 0);
			else
				_color = color(1., 1., 1.);
		}
		~Particle(){}
		void draw();
		void update(long unsigned int dt);
		void reset(position pac);
		position getPos(){ return _actual; }
		bool isDead(){ return _isDead; }		
};
#endif
