#include "DirecLight.h"

void DirecLight::setupLight(position pacpos, int dir){}

void DirecLight::giveLight(){
	glClearColor(0.1f, 0.5f, .8f, 1.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, _light_vect);
	glLightfv(GL_LIGHT0, GL_AMBIENT, _light_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _light_Ks);
}
