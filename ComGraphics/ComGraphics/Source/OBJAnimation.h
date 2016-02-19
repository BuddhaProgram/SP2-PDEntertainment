#ifndef OBJANIMATION_H
#define OBJANIMATION_H

#include "Camera3.h"

class Animation
{
public:
	Animation();
	~Animation();

	void Collapsing(double dt);
	void OBJAnimation(double dt);
	void OpenMainDoor(double dt);
	void Portraits(double dt);

	float PlanetRotate;
	float AsteroidRotate;
	float AsteroidRotateF;
	float AsteroidMove;
	float AsteroidMoveS;

	Camera3 camera;

	float OpenDoorL;
	bool toOpenDoorL = false;
	float OpenDoorR;
	bool toOpenDoorR = false;

	float RubbleCollapse;
	bool Collapse = false;

	float PortraitDrop;
	float PortraitFall;
	bool toPortraitDrop = false;
	bool toPortraitFall = false;

	bool cameramove1 = false;
	bool cameramove2 = false;
	bool cameramove3 = false;

};

#endif