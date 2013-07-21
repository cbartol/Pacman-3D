#ifndef __BALL_H__
#define __BALL_H__

#include "conventions.h"

class Ball{
	protected:
		position _pos;
		bool _eaten;
		int _points;
		bool _special;
	public:
		Ball(float x, float y , int p = 200, bool sp = false): _pos(x, y, -0.2), _eaten(false), _points(p), _special(sp){
		}
		virtual ~Ball(){}
		
		virtual void draw();
		virtual int eaten();
		bool wasEaten();
		bool isSpecial();

};
#endif
