#include "Misc.h"
misc::misc()
{

}
misc::~misc()
{

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