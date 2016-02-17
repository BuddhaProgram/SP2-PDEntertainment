#include "Misc.h"
misc::misc()
{

}
misc::~misc()
{

}
bool misc::proximitycheck(float smallx, float largex, float smallz, float largez)
{
	//this function checks if the camera is close to a side of the object
	bool result = false;
	if ((camX >= smallx - 2.f) && (camX <= smallx) && (camZ >= smallz) && (camZ <= largez)){ result = true; }
	if ((camX <= largex + 2.f) && (camX >= largex) && (camZ >= smallz) && (camZ <= largez)){ result = true; }
	if ((camX >= smallx) && (camX <= largex) && (camZ >= smallz - 2.f) && (camZ <= smallz)){ result = true; }
	if ((camX >= smallx) && (camX <= largex) && (camZ <= largez + 2.f) && (camZ >= largez)){ result = true; }
	return result;
}

bool misc::hitting(float smallx, float largex, float smallz, float largez)
{//height must only be within +9 to +11.
	bool result = false;
	float dist = 3.f;

	return result;
}

bool misc::WithinArea(float smallx, float largex, float smallz, float largez)
{//checks if camera is within a certain area of the room.
	if ((camX > smallx)
		&&
		(camX < largex)
		&&
		(camZ > smallz)
		&&
		(camZ < largez)
		)
	{
		return true;
	}
	return false;
}

bool misc::Interacting(float smallx, float largex, float smallz, float largez)
{
	if (proximitycheck(smallx, largex, smallz, largez) == true && Application::IsKeyPressed('E'))
	{
		return true;
	}
	return false;
}