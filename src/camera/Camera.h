#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../conventions.h"
#include <GL/glut.h>

class Game;
class Camera {
	protected:
		position _camPos;
		position _camDest;
	public:
		Camera() {}
		virtual ~Camera() {}

		virtual void update(Game *g, long unsigned int dt) = 0;
		virtual void setCamera() = 0;
		virtual void setProjectionMode(double width, double height) = 0;
		virtual char convertDirection(Game *g, char dir) = 0;
};
#endif
