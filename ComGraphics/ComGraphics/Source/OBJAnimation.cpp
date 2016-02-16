#include "OBJAnimation.h"
#include "Vector3.h"
#include "Mtx44.h"

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
		RubbleCollapse -= (float)(50 * dt);
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
		if (PortraitDrop >= 0)
		{
			toPortraitDrop = true;
		}
		if (PortraitDrop <= -4)
		{
			toPortraitDrop = false;
			toPortraitFall = true;
		}
		if (PortraitFall >= 90)
		{
			toPortraitFall = false;
		}

		if (toPortraitDrop)
		{
			PortraitDrop -= (float)(50 * dt);
		}
		if (toPortraitFall)
		{
			PortraitFall += (float)(40 * dt);
		}

}
