#include "Misc.h"
misc::misc()
{

}
misc::~misc()
{

}

float getAngle(const Vector3 &view, const Vector3 &target)
{
	float MagnitudeA = sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
	float MagnitudeB = sqrt(pow(target.x, 2) + pow(target.y, 2) + pow(target.z, 2));
	float dotProduct = view.x * target.x + view.y * target.y + view.z * target.z;

	float angle = acos(dotProduct / (MagnitudeA * MagnitudeB));

	return Math::RadianToDegree(angle);
}

//bool misc::hitting(float distance, float mobx, float mobz, float AOA)
//{
//	bool result = false;
//	
//	float currDist = sqrt((camera.position.x - mobx) * (camera.position.x - mobx)
//		(camera.position.z - mobz) * (camera.position.z - mobz));
//
//	if (currDist <= distance)
//	{
//		if ((getAngle(camera.view, Vector3(mobx,0,mobz) - camera.position)) <= AOA) 
//		{
//			result = true;
//		}
//	}
//
//	return result;
//}

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