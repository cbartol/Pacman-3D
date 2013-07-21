#ifndef __PACMAN_H__
#define __PACMAN_H__

#include "../conventions.h"
#include <vector>
#include <stdlib.h>
#include "Particle.h"
#define pac_radius 0.5

class Pacman{
	protected:
		float _xcoord;
		float _ycoord;
		bool _up, _down, _left, _right, _isDead;
		position _leftEye;
		position _rightEye;
		position _leftEyebrows;
		position _rightEyebrows;
		std::vector<Particle *> _particles;

	public:
		Pacman(float x, float y): _xcoord(x), _ycoord(y), _up(false), _down(true), _left(false), _right(false), _isDead(false),
						_leftEye(XX(pac_radius, 3.*PI/4., PI/4.), YY(pac_radius, 3.*PI/4., PI/4.), ZZ(pac_radius, 3.*PI/4., -PI/4.)-0.1),
						_rightEye(XX(pac_radius, PI/4., PI/4.), YY(pac_radius, PI/4., PI/4.), ZZ(pac_radius, PI/4., PI/4.)-0.1),
						_leftEyebrows(XX(pac_radius, 3.*PI/5., PI/3.), YY(pac_radius, 3.*PI/5., PI/3.), ZZ(pac_radius, 3.*PI/5., PI/3.)),
						_rightEyebrows(XX(pac_radius, 2.*PI/5., PI/3.), YY(pac_radius, 2.*PI/5., PI/3.), ZZ(pac_radius, 2.*PI/5., PI/3.)){
			int nump = (rand() % 1001) + 500;
			for (int  i =0; i < nump; i++){
				_particles.push_back(new Particle());
			} 
		}
		virtual ~Pacman(){
			int i, size;
			for(i = 0, size = _particles.size(); i < size; i++)
				delete _particles[i];		
		}
		virtual void draw(bool gameOver, bool gameWin) = 0;
		void bang();
		void setDirection(int dir);
		void stop();
		void move(position dest);
		position premove(long unsigned int dt);
		bool isDirectionSet();
		int getDirection();
		position getPos(){ return position(_xcoord, _ycoord, 0); }	
		bool isDead(){ return _isDead;}	
		void explosion(long unsigned int dt);
		static void replacing(int value);
};
#endif
