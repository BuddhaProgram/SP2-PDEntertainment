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

	float QPDOOR4_TOP;
	float QPDOOR4_BOT;
	bool QP_TOPDOOR4 = false;
	bool QP_BOTDOOR4 = false;

	float QPDOOR5_TOP;
	float QPDOOR5_BOT;
	bool QP_TOPDOOR5 = false;
	bool QP_BOTDOOR5 = false;
};

#endif