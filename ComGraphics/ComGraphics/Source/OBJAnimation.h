/**************************************************************************/
/*!
\file			OBJAnimation.h
\author			Matsuda Kenichi
\par			email: 150450F\@mymail.nyp.edu.sg
\brief
Class to define all animation
*/
/**************************************************************************/

#ifndef OBJANIMATION_H
#define OBJANIMATION_H

#include "Camera3.h"

/**************************************************************************/
/*!
Class Animation:
\brief
Define Animation and its method make object move on it owns.
*/
/**************************************************************************/

class Animation
{
public:
	Animation(); //Default constructor
	~Animation(); // Destructor

	void Collapsing(double dt);				//Function to make rubble collapse
	void OBJAnimation(double dt);			//Function to make obj animated
	void OpenMainDoor(double dt);			//Function to make CutScene door animation
	void Portraits(double dt);				//Function to make the Portrait falling animation

	//Functions for Doors opening and closing animation
	void OpenSlideDoor1(double dt);			
	void OpenSlideDoor2(double dt);
	void CloseSlideDoor2(double dt);
	void OpenSlideDoor3(double dt);
	void CloseSlideDoor3(double dt);
	void OpenSlideDoor4(double dt);
	void CloseSlideDoor4(double dt);
	void OpenSlideDoor_Boss(double dt);
	void CloseSlideDoor_Boss(double dt);
	void CloseSlideDoor5(double dt);

	//Function for ship animation
	void ShipTakeOff(double dt);

	//Check function to see if char is within certaain area
	bool WithinArea(float smallx, float largex, float smallz, float largez);
	float cam_pos_X, cam_poz_Z;

	/*Variables and Bools*/

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

	float f_PortraitDrop = 6;
	float f_PortraitFall;
	bool b_toPortraitDrop = false;
	bool b_toPortraitFall = false;

	bool cameramove1 = false;
	bool cameramove2 = false;
	bool cameramove3 = false;

	float DoorSlideTop;
	float DoorSlideBtm;
	bool toSlideDoorTop = true;
	bool toSlideDoorBtm = true;

	float DoorSlideTop_2;
	float DoorSlideBtm_2;
	bool toSlideDoorTop2 = true;
	bool toSlideDoorBtm2 = true;
	bool ClosingDoorTop2 = true;
	bool ClosingDoorBtm2 = true;

	float DoorSlideTop_3;
	float DoorSlideBtm_3;
	bool toSlideDoorTop3 = true;
	bool toSlideDoorBtm3 = true;
	bool ClosingDoorTop3 = true;
	bool ClosingDoorBtm3 = true;

	float DoorSlideTop_Boss;
	float DoorSlideBtm_Boss;
	bool toSlideDoorTop_Boss = true;
	bool toSlideDoorBtm_Boss = true;
	bool ClosingDoorTop_Boss = true;
	bool ClosingDoorBtm_Boss = true;

	float DoorSlideTop_4;
	float DoorSlideBtm_4;
	bool toSlideDoorTop4 = true;
	bool toSlideDoorBtm4 = true;
	bool ClosingDoorTop4 = true;
	bool ClosingDoorBtm4 = true;

	float DoorSlideTop_5 = 10;
	float DoorSlideBtm_5 = -6;
	bool ClosingDoorTop5 = true;
	bool ClosingDoorBtm5 = true;

	float MovingShip;
	float MovingShip2;
	bool shipCheck1 = true;
	bool shipCheck2 = false;
};

#endif