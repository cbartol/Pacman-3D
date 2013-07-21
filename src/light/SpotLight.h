#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include "Light.h"
#include <GL/glut.h>

class SpotLight : public Light{
	private:
		GLfloat _light_spot[4];
		GLfloat _direction[3];
		GLfloat _theta;
		GLfloat _alpha;
		GLfloat _light_Ka[4];
		GLfloat _light_Kd[4];
		GLfloat _light_Ks[4];
	public:
		SpotLight(): _theta(45.), _alpha(5.){	// _theta -> cutoff angle; _alpha -> exponent
			glEnable(GL_LIGHT1);
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
		~SpotLight(){
			glDisable(GL_LIGHT1);
		}
		void enable(){ glEnable(GL_LIGHT1); }
		void setupLight(position pacpos, int dir);
		void giveLight();
};
#endif
