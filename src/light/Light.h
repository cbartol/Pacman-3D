#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "../conventions.h"
#include <GL/glut.h>
class Light{
	private:

	public:
		Light() {}
		virtual ~Light(){}
		virtual void setupLight(position pacpos, int dir) = 0;
		virtual void giveLight() = 0;
		virtual void enable() = 0;
};
#endif
