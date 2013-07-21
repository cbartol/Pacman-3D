#include "SpotLight.h"

void SpotLight::setupLight(position pacpos, int dir){
	double n;
	_direction[0] = _direction[1] = 0;
	_direction[2] = -0.4;			// Para "inclinar" a spotlight para baixo
	_light_spot[0] = pacpos.x;
	_light_spot[1] = pacpos.y;
	_light_spot[2] = pacpos.z + 0.51;
	_light_spot[3] = 1.0;

	// Posição/Direcção da Luz de acordo com a direcção do Pacman
	if(dir == UP){
		_light_spot[1] = pacpos.y - 0.25;
		_direction[1] = 2.;
	}else if (dir == DOWN){
		_light_spot[1] = pacpos.y + 0.25;
		_direction[1] = -2.;
	}else if (dir == RIGHT){
		_light_spot[0] = pacpos.x - 0.25;
		_direction[0] = 2.;
	}else if (dir == LEFT){
		_light_spot[0] = pacpos.x + 0.25;
		_direction[0] = -2.;
	}else
		_direction[2] = -1.;
		
	// Normalização do vector da direcção da spotlight	
	n = sqrt(_direction[0]*_direction[0] + _direction[1]*_direction[1] + _direction[2]*_direction[2]);
	_direction[0] = _direction[0]/n;
	_direction[1] = _direction[1]/n;
	_direction[2] = _direction[2]/n;
}

void SpotLight::giveLight(){			// O nome diz tudo...
	glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
	glLightfv(GL_LIGHT1, GL_AMBIENT, _light_Ka);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, _light_Kd);
	glLightfv(GL_LIGHT1, GL_SPECULAR, _light_Ks);
	glLightfv(GL_LIGHT1, GL_POSITION, _light_spot);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, _direction);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &_theta);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, &_alpha);
}
