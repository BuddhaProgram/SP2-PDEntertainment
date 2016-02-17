#ifndef TOOLS_H
#define TOOLS_H

#include"Assignment3.h"
#include "Camera3.h"

class Tools
{
public:
	Tools();
	~Tools();

	bool proximitycheck(float smallx, float largex, float smallz, float largez);
	bool WithinArea(float smallx, float largex, float smallz, float largez);
	bool Interacting(float smallx, float largex, float smallz, float largez);
	void Collision(float smallx, float largex, float smallz, float largez);

	Camera3 camera;
};



#endif