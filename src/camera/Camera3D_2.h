#ifndef __CAMERA3D_2_H__
#define __CAMERA3D_2_H__

#include "Camera.h"
#include <map>

class Camera3D_2 : public Camera {
	private:
		std::map<char, char> _up;
		std::map<char, char> _down;
		std::map<char, char> _left;
		std::map<char, char> _right;
		
	public:
		Camera3D_2(Game *g);
		virtual ~Camera3D_2(){
		}
		void update(Game *g, long unsigned int dt);
		void setCamera();
		void setProjectionMode(double width, double height);
		char convertDirection(Game *g, char dir);
};
#endif
