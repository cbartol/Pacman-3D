#ifndef __DIRECLIGHT_H__
#define __DIRECLIGHT_H__

#include "Light.h"
#include <GL/glut.h>
class DirecLight : public Light{
	private:
		GLfloat _light_vect[4];
		GLfloat _light_Ka[4];
		GLfloat _light_Kd[4];
		GLfloat _light_Ks[4];
	public:
		DirecLight() {
			glEnable(GL_LIGHT0);
			// Luz Direccional
			_light_vect[0] = -1.2;
			_light_vect[1] = -1.4;
			_light_vect[2] = 3.0;
			_light_vect[3] = 0.0;
			// Componente Ambiente
			_light_Ka[0] = 0.0;
			_light_Ka[1] = 0.0;
			_light_Ka[2] = 0.0;
			_light_Ka[3] = 1.0;
			// Componente Difusa
			_light_Kd[0] = 1.0;
			_light_Kd[1] = 1.0;
			_light_Kd[2] = 1.0;
			_light_Kd[3] = 1.0;
			// Componente Especular
			_light_Ks[0] = 1.0;
			_light_Ks[1] = 1.0;
			_light_Ks[2] = 1.0;
			_light_Kd[3] = 1.0;
		}
		~DirecLight(){
			glDisable(GL_LIGHT0);
		}
		void enable(){ glEnable(GL_LIGHT0); }
		void setupLight(position pacpos, int dir);
		void giveLight();
};
#endif
