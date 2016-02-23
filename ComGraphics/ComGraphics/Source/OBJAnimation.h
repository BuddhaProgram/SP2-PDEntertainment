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
	void OpenSlideDoor(double dt);

	bool WithinArea(float smallx, float largex, float smallz, float largez);
	float cam_pos_X, cam_poz_Z;

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

	float RubbleCollapse = 100;
	bool Collapse = false;

	float PortraitDrop;
	float PortraitFall;
	bool toPortraitDrop = false;
	bool toPortraitFall = false;

	bool cameramove1 = false;
	bool cameramove2 = false;
	bool cameramove3 = false;

	float DoorSlideTop;
	float DoorSlideBtm;
	bool toSlideDoorTop = true;
	bool toSlideDoorBtm = true;

};

#endif