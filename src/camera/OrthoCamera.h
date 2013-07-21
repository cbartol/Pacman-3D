#ifndef __ORTHOCAMERA_H__
#define __ORTHOCAMERA_H__

#include "Camera.h"

class OrthoCamera : public Camera {

	public:
		OrthoCamera() {
		}
		virtual ~OrthoCamera(){
		}
		void update(Game *g, long unsigned int dt);
		void setCamera();
		void setProjectionMode(double width, double height);
		char convertDirection(Game *g, char dir);
};
#endif
