#include "OBJAnimation.h"
#include "Vector3.h"
#include "Mtx44.h"
#include "Camera3.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Collapsing(double dt)
{
	//Rubble Falling~
	if (Collapse)
	{
		RubbleCollapse -= (float)(200 * dt);
	}
	
}

void Animation::OBJAnimation(double dt)
{
	PlanetRotate += (float)(50 * dt);
	AsteroidRotate += (float)(50 * dt);
	AsteroidRotateF += (float)(150 * dt);

	AsteroidMove += (float)(10 * dt);
	if (AsteroidMove >= 100)
	{
		AsteroidMove = -100;
	}
	AsteroidMoveS += (float)(1 * dt);
	if (AsteroidMoveS >= 100)
	{
		AsteroidMoveS = -100;
	}
}

void Animation::OpenMainDoor(double dt)
{
	//left door
	if (OpenDoorL <= -75)
	{

		toOpenDoorL = false;
		Collapse = true;
		if (RubbleCollapse <= -10)
		{
			Collapse = false;
			/*		toPortraitDrop = true;
			if (PortraitDrop <= -4)
			{
			toPortraitDrop = false;
			toPortraitFall = true;
			if (PortraitFall >= 90)
			{
			toPortraitFall = false;
			}
			}*/
		}

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

void Animation::Portraits(double dt)
{
	if (f_PortraitDrop >= 6)
	{
		b_toPortraitDrop = true;
	}

	if (f_PortraitDrop <= 4.5f)
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
		f_PortraitFall += (float)(50 * dt);
	}

	if (f_PortraitFall >= 90)
	{
		f_PortraitFall = 90;
		b_toPortraitFall = false;
	}
}

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
