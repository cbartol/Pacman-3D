#ifndef __CAMERA3D_1_H__
#define __CAMERA3D_1_H__

#include "Camera.h"

class Camera3D_1 : public Camera {
	private:

	public:
		Camera3D_1(Game *g);
		virtual ~Camera3D_1(){
		}
		void update(Game *g, long unsigned int dt);
		void setCamera();
		void setProjectionMode(double width, double height);
		char convertDirection(Game *g, char dir);
};
#endif
