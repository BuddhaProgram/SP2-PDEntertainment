#ifndef TOOLS_H
#define TOOLS_H

#include "Application.h"
#include "Camera3.h"

class misc
{
public:
	misc();
	~misc();

	bool proximitycheck(float smallx, float largex, float smallz, float largez);
	bool WithinArea(float smallx, float largex, float smallz, float largez);
	bool Interacting(float smallx, float largex, float smallz, float largez);
	bool hitting(float smallx, float largex, float smallz, float largez);

	float camX, camY, camZ;
};



#endif