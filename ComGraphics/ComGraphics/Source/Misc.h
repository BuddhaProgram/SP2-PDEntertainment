#ifndef TOOLS_H
#define TOOLS_H

#include "Application.h"
#include "Camera3.h"

class misc
{
public:
	misc();
	~misc();

	bool WithinArea(float smallx, float largex, float smallz, float largez);
	bool hitting(float distance, float mobx, float mobz, float AOA); // AOA is angle of attack

	float camX, camY, camZ;
};
#endif