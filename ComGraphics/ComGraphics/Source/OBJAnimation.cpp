/**************************************************************************/
/*!
\file			OBJAnimation.cpp
\author			Matsuda Kenichi
\par			email: 150450F@mymail.nyp.edu.sg
\brief
File containing function to make animation work
*/
/**************************************************************************/

#include "OBJAnimation.h"
#include "Vector3.h"
#include "Mtx44.h"
#include "Camera3.h"

Animation::Animation()
{
	OpenDoorL = 0;
	OpenDoorR = 0;
	toOpenDoorL = false;
	toOpenDoorR = false;
	RubbleCollapse = 100;
	Collapse = false;
	f_PortraitDrop = 6;
	f_PortraitFall = 0;
	 b_toPortraitDrop = false;
	 b_toPortraitFall = false;

	 cameramove1 = false;
	 cameramove2 = false;
	 cameramove3 = false;

	 DoorSlideTop = 0;
	 DoorSlideBtm = 0;
	 toSlideDoorTop = true;
	 toSlideDoorBtm = true;

	 DoorSlideTop_2 = 0;
	 DoorSlideBtm_2 = 0;
	 toSlideDoorTop2 = true;
	 toSlideDoorBtm2 = true;
	 ClosingDoorTop2 = true;
	 ClosingDoorBtm2 = true;

	 DoorSlideTop_3 = 0;
	 DoorSlideBtm_3 = 0;
	 toSlideDoorTop3 = true;
	 toSlideDoorBtm3 = true;
	 ClosingDoorTop3 = true;
	 ClosingDoorBtm3 = true;

	 DoorSlideTop_Boss = 0;
	 DoorSlideBtm_Boss = 0;
	 toSlideDoorTop_Boss = true;
	 toSlideDoorBtm_Boss = true;
	 ClosingDoorTop_Boss = true;
	 ClosingDoorBtm_Boss = true;

	 DoorSlideTop_4 = 0;
	 DoorSlideBtm_4 = 0;
	 toSlideDoorTop4 = true;
	 toSlideDoorBtm4 = true;
	 ClosingDoorTop4 = true;
	 ClosingDoorBtm4 = true;

	 DoorSlideTop_5 = 10;
	 DoorSlideBtm_5 = -6;
	 ClosingDoorTop5 = true;
	 ClosingDoorBtm5 = true;

	 MovingShip = 0;
	 MovingShip2 = 0;
	 shipCheck1 = true;
	 shipCheck2 = false;

	  OpenDoor6 = false;

	  OpenDoor7 = false;

	  OpenDoor8 = false;

	  OpenDoor9 = false;

	  OpenDoor10 = false;
}

Animation::~Animation()
{
}

/**************************************************************************/
/*!
\brief
Function for Rubble Collapsing animation
\param dt
	dt = delta time
\bool Collapse
	If true , rubble falling animation will activate.
\float RubbleCollapse
	speed of the rubble falling animation
*/
/**************************************************************************/

void Animation::Collapsing(double dt)
{
	//Rubble Falling~
	if (Collapse) //if Collapse is true, rubble will fall
	{
		RubbleCollapse -= (float)(200 * dt);
	}
	
}

/**************************************************************************/
/*!
\brief
Function for Opening Main Door animation on the first cutscene
\param dt
	dt = delta time
\bool OpenDoorL, OpenDoorR
	If true , door opening animation willa activate
\float toOpenDoorL, toOpenDoorR
	speed of the door opening animation
*/
/**************************************************************************/

void Animation::OpenMainDoor(double dt)
{
	//left door
	if (OpenDoorL <= -75) // if OpenDoorL is less than 75, animation will stop
	{

		toOpenDoorL = false;

	}
	if (OpenDoorL >= 0)
	{
		toOpenDoorL = true;

	}

	if (toOpenDoorL)
	{
		OpenDoorL -= (float)(10 * dt);
		if (OpenDoorL <= -35)
		{
			OpenDoorL -= (float)(20 * dt);
		}
	}



	//rightdoor
	if (OpenDoorR >= 76)
	{
		toOpenDoorR = false;
	}
	if (OpenDoorR <= 0)
	{
		toOpenDoorR = true;
	}

	if (toOpenDoorR)
	{
		OpenDoorR += (float)(10 * dt);
		if (OpenDoorR >= 35)
		{
			OpenDoorR += (float)(20 * dt);
		}
	}
}

/**************************************************************************/
/*!
\brief
Function for Falling Portraits animation
\param dt
	dt = delta time
\bool b_toPortraitDrop, b_toPortraitFall
	If true , the portrait falling and dropping animation will activate
\float f_PortraitDrop, f_PortraitFall
	speed of the portrait dropping and falling animation
*/
/**************************************************************************/

void Animation::Portraits(double dt)
{
	if (f_PortraitDrop >= 6)
	{
		b_toPortraitDrop = true;
	}

	if (f_PortraitDrop <= 4.3f)
	{
		b_toPortraitDrop = false;
		b_toPortraitFall = true;
	}

	if (b_toPortraitDrop)
	{
		f_PortraitDrop -= (float)(50 * dt);
	}

	if (b_toPortraitFall)
	{
		f_PortraitFall += (float)(200 * dt);
	}

	if (f_PortraitFall >= 90)
	{
		f_PortraitFall = 90;
		b_toPortraitFall = false;
	}
}

/**************************************************************************/
/*!
\author			Matsuda Kenichi , Zheng QingPing
\brief
Functions for Slide Door animation
\param dt
	dt = delta time
\bool 
	toSlideDoorTop, to SlideDoorBtm, toSlideDoorTop2, toSlideDoorBtm2, ClosingDoorTop2, 
	ClosingDoorBtm2, toSlideDoorTop3 ,toSlideDoorBtm3, ClosingDoorTop3, ClosingDoorBtm3,
	toSlideDoorTop_Boss, toSlideDoorBtm_Boss, ClosingDoorTop_Boss, ClosingDoorBtm_Boss,
	toSlideDoorTop4, toSlideDoorBtm4, ClosingDoorTop4, ClosingDoorBtm4, ClosingDoorTop5, ClosingDoorBtm5,
	QP_TOPDOOR1, QP_BTMDOOR1, QP_TOPDOOR2, QP_BTMDOOR2, QP_TOPDOOR3, QP_BTMDOOR3, QP_TOPDOOR4, QP_BTMDOOR4, 
	QP_TOPDOOR5, QP_BTMDOOR5,
	
	If true , the animation for Door to Open and Close will activate.

\float 
	DoorSlideTop, DoorSlideBtm, DoorSlideTop_2, DoorSlideBtm_2, DoorSlideTop_3, DoorSlideBtm_3,
	oorSlideTop_Boss, DoorSlideBtm_Boss, DoorSlideTop_4, DoorSlideBtm_4, DoorSlideTop_5, DoorSlideBtm_5,
	QPDOOR1_TOP, QPDOOR1_BTM, QPDOOR2_TOP, QPDOOR2_BTM,  QPDOOR3_TOP, QPDOOR3_BTM, QPDOOR4_TOP, QPDOOR4_BTM,
	QPDOOR5_TOP, QPDOOR5_BTM

	speed of the door opening and closing animation
*/
/**************************************************************************/


void Animation::OpenSlideDoor1(double dt)
{
	if (toSlideDoorTop)
	{
		DoorSlideTop += (float)(8 * dt);
		if (DoorSlideTop >= 10)
		{
			toSlideDoorTop = false;
		}
	}


	if (toSlideDoorBtm)
	{
		DoorSlideBtm -= (float)(5 * dt);
		if (DoorSlideBtm <= -6)
		{
			toSlideDoorBtm = false;
		}
	}

}

void Animation::OpenSlideDoor2(double dt)
{
	if (toSlideDoorTop2)
	{
		DoorSlideTop_2 += (float)(8 * dt);
		if (DoorSlideTop_2 >= 10)
		{
			toSlideDoorTop2 = false;
		}
	}

	if (toSlideDoorBtm2)
	{
		DoorSlideBtm_2 -= (float)(5 * dt);
		if (DoorSlideBtm_2 <= -6)
		{
			toSlideDoorBtm2 = false;
		}
	}
}

void Animation::CloseSlideDoor2(double dt)
{
	if (ClosingDoorTop2)
	{
		DoorSlideTop_2 -= (float)(8 * dt);
		if (DoorSlideTop_2 <= 0)
		{
			ClosingDoorTop2 = false;
		}
	}

	if (ClosingDoorBtm2)
	{
		DoorSlideBtm_2 += (float)(5 * dt);
		if (DoorSlideBtm_2 >= 0)
		{
			ClosingDoorBtm2 = false;
		}
	}
}

void Animation::OpenSlideDoor3(double dt)
{
	if (toSlideDoorTop3)
	{
		DoorSlideTop_3 += (float)(8 * dt);
		if (DoorSlideTop_3 >= 10)
		{
			toSlideDoorTop3 = false;
		}
	}

	if (toSlideDoorBtm3)
	{
		DoorSlideBtm_3 -= (float)(5 * dt);
		if (DoorSlideBtm_3 <= -6)
		{
			toSlideDoorBtm3 = false;
		}
	}

}

void Animation::CloseSlideDoor3(double dt)
{
	if (ClosingDoorTop3)
	{
		DoorSlideTop_3 -= (float)(8 * dt);
		if (DoorSlideTop_3 <= 0)
		{
			ClosingDoorTop3 = false;
		}
	}

	if (ClosingDoorBtm3)
	{
		DoorSlideBtm_3 += (float)(5 * dt);
		if (DoorSlideBtm_3 >= 0)
		{
			ClosingDoorBtm3 = false;
		}
	}
}

void Animation::OpenSlideDoor_Boss(double dt)
{
	if (toSlideDoorTop_Boss)
	{
		DoorSlideTop_Boss += (float)(8 * dt);
		if (DoorSlideTop_Boss >= 10)
		{
			toSlideDoorTop_Boss = false;
		}
	}

	if (toSlideDoorBtm_Boss)
	{
		DoorSlideBtm_Boss -= (float)(5 * dt);
		if (DoorSlideBtm_Boss <= -6)
		{
			toSlideDoorBtm_Boss = false;
		}
	}

}

void Animation::CloseSlideDoor_Boss(double dt)
{
	if (ClosingDoorTop_Boss)
	{
		DoorSlideTop_Boss -= (float)(8 * dt);
		if (DoorSlideTop_Boss <= 0)
		{
			ClosingDoorTop_Boss = false;
		}
	}

	if (ClosingDoorBtm_Boss)
	{
		DoorSlideBtm_Boss += (float)(5 * dt);
		if (DoorSlideBtm_Boss >= 0)
		{
			ClosingDoorBtm_Boss = false;
		}
	}
}

void Animation::OpenSlideDoor4(double dt)
{
	if (toSlideDoorTop4)
	{
		DoorSlideTop_4 += (float)(8 * dt);
		if (DoorSlideTop_4 >= 10)
		{
			toSlideDoorTop4 = false;
		}
	}

	if (toSlideDoorBtm4)
	{
		DoorSlideBtm_4 -= (float)(5 * dt);
		if (DoorSlideBtm_4 <= -6)
		{
			toSlideDoorBtm4 = false;
		}
	}

}

void Animation::CloseSlideDoor4(double dt)
{
	if (ClosingDoorTop4)
	{
		DoorSlideTop_4 -= (float)(8 * dt);
		if (DoorSlideTop_4 <= 0)
		{
			ClosingDoorTop4 = false;
		}
	}

	if (ClosingDoorBtm4)
	{
		DoorSlideBtm_4 += (float)(5 * dt);
		if (DoorSlideBtm_4 >= 0)
		{
			ClosingDoorBtm4 = false;
		}
	}
}

void Animation::CloseSlideDoor5(double dt)
{
	if (ClosingDoorTop5)
	{
		DoorSlideTop_5 -= (float)(8 * dt);
		if (DoorSlideTop_5 <= 0)
		{
			ClosingDoorTop5 = false;
		}
	}

	if (ClosingDoorBtm5)
	{
		DoorSlideBtm_5 += (float)(5 * dt);
		if (DoorSlideBtm_5 >= 0)
		{
			ClosingDoorBtm5 = false;
		}
	}
}

void Animation::OpenQPDOOR1(double dt)
{
	if (QP_TOPDOOR1)
	{
		QPDOOR1_TOP += (float)(8 * dt);
		if (QPDOOR1_TOP >= 10)
		{
			QP_TOPDOOR1 = false;
		}
	}

	if (QP_BOTDOOR1)
	{
		QPDOOR1_BOT -= (float)(5 * dt);
		if (QPDOOR1_BOT <= -6)
		{
			QP_BOTDOOR1 = false;
		}
	}
}

void Animation::OpenQPDOOR2(double dt)
{
	if (QP_TOPDOOR2)
	{
		QPDOOR2_TOP += (float)(8 * dt);
		if (QPDOOR2_TOP >= 10)
		{
			QP_TOPDOOR2 = false;
		}
	}

	if (QP_BOTDOOR2)
	{
		QPDOOR2_BOT -= (float)(5 * dt);
		if (QPDOOR2_BOT <= -6)
		{
			QP_BOTDOOR2 = false;
		}
	}
}

void Animation::OpenQPDOOR3(double dt)
{
	if (QP_TOPDOOR3)
	{
		QPDOOR3_TOP += (float)(8 * dt);
		if (QPDOOR3_TOP >= 10)
		{
			QP_TOPDOOR3 = false;
		}
	}

	if (QP_BOTDOOR3)
	{
		QPDOOR3_BOT -= (float)(5 * dt);
		if (QPDOOR3_BOT <= -6)
		{
			QP_BOTDOOR3 = false;
		}
	}
}

void Animation::OpenQPDOOR4(double dt)
{
	if (QP_TOPDOOR4)
	{
		QPDOOR4_TOP -= (float)(8 * dt);
		if (QPDOOR4_TOP <= 0)
		{
			QP_TOPDOOR4 = false;
		}
	}

	if (QP_BOTDOOR4)
	{
		QPDOOR4_BOT += (float)(5 * dt);
		if (QPDOOR4_BOT >= 0)
		{
			QP_BOTDOOR4 = false;
		}
	}
}

void Animation::OpenQPDOOR5(double dt)
{
	if (QP_TOPDOOR5)
	{
		QPDOOR5_TOP += (float)(8 * dt);
		if (QPDOOR5_TOP >= 10)
		{
			QP_TOPDOOR5 = false;
		}
	}

	if (QP_BOTDOOR5)
	{
		QPDOOR5_BOT -= (float)(5 * dt);
		if (QPDOOR5_BOT <= -6)
		{
			QP_BOTDOOR5 = false;
		}
	}
}

bool Animation::WithinArea(float smallx, float largex, float smallz, float largez)
{//checks if camera is within a certain area of the room.
	bool result = false;
	if (camera.position.x >= smallx && camera.position.x <= largex && camera.position.z >= smallz && camera.position.z <= largez)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

/**************************************************************************/
/*!
\brief
Function for Ship taking off animation
\param dt
	dt = delta time
\bool shipCheck1, shipCheck2
	If true , the ship translation animation will activate.
\float MovingShip, MovingShip2
	speed of the ship translate animation.
*/
/**************************************************************************/

void Animation::ShipTakeOff(double dt)
{
	if (shipCheck1)
	{
		MovingShip += (float)(10 * dt);
	}

	if (shipCheck2)
	{
		MovingShip2 += (float)(100.0f * dt);
	}

	if (MovingShip >= 20)
	{
		shipCheck1 = false;
		shipCheck2 = true;
	}
}
