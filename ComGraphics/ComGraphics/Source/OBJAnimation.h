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

	void OpenQPDOOR1(double dt);
	void OpenQPDOOR2(double dt);
	void OpenQPDOOR3(double dt);
	void OpenQPDOOR4(double dt);
	void OpenQPDOOR5(double dt);

	void ShipTakeOff(double dt);


	bool WithinArea(float smallx, float largex, float smallz, float largez);
	float cam_pos_X, cam_poz_Z;

	float PlanetRotate;
	float AsteroidRotate;
	float AsteroidRotateF;
	float AsteroidMove;
	float AsteroidMoveS;

	Camera3 camera;

	float OpenDoorL;
	bool toOpenDoorL;
	float OpenDoorR;
	bool toOpenDoorR;

	float RubbleCollapse;
	bool Collapse;

	float f_PortraitDrop;
	float f_PortraitFall;
	bool b_toPortraitDrop;
	bool b_toPortraitFall;

	bool cameramove1;
	bool cameramove2;
	bool cameramove3;

	float DoorSlideTop;
	float DoorSlideBtm;
	bool toSlideDoorTop;
	bool toSlideDoorBtm;

	float DoorSlideTop_2;
	float DoorSlideBtm_2;
	bool toSlideDoorTop2;
	bool toSlideDoorBtm2;
	bool ClosingDoorTop2;
	bool ClosingDoorBtm2;

	float DoorSlideTop_3;
	float DoorSlideBtm_3;
	bool toSlideDoorTop3;
	bool toSlideDoorBtm3;
	bool ClosingDoorTop3;
	bool ClosingDoorBtm3;

	float DoorSlideTop_Boss;
	float DoorSlideBtm_Boss;
	bool toSlideDoorTop_Boss;
	bool toSlideDoorBtm_Boss;
	bool ClosingDoorTop_Boss;
	bool ClosingDoorBtm_Boss;

	float DoorSlideTop_4;
	float DoorSlideBtm_4;
	bool toSlideDoorTop4;
	bool toSlideDoorBtm4;
	bool ClosingDoorTop4;
	bool ClosingDoorBtm4;


	float DoorSlideTop_5;
	float DoorSlideBtm_5;
	bool ClosingDoorTop5;
	bool ClosingDoorBtm5;

	float MovingShip;
	float MovingShip2;
	bool shipCheck1;
	bool shipCheck2;

	bool OpenDoor6;

	bool OpenDoor7;

	bool OpenDoor8;

	bool OpenDoor9;

	bool OpenDoor10;

	float QPDOOR1_TOP;
	float QPDOOR1_BOT;
	bool QP_TOPDOOR1 = false;
	bool QP_BOTDOOR1 = false;

	float QPDOOR2_TOP;
	float QPDOOR2_BOT;
	bool QP_TOPDOOR2 = false;
	bool QP_BOTDOOR2 = false;

	float QPDOOR3_TOP;
	float QPDOOR3_BOT;
	bool QP_TOPDOOR3 = false;
	bool QP_BOTDOOR3 = false;

	float QPDOOR4_TOP = 10;
	float QPDOOR4_BOT = -6;
	bool QP_TOPDOOR4 = false;
	bool QP_BOTDOOR4 = false;


	float QPDOOR5_TOP;
	float QPDOOR5_BOT;
	bool QP_TOPDOOR5 = false;
	bool QP_BOTDOOR5 = false;

	float MovingShip;
	float MovingShip2;
	bool shipCheck1 = true;
	bool shipCheck2 = false;
};

#endif