#include "Tools.h"
Tools::Tools()
{

}
Tools::~Tools()
{

}
bool Tools::proximitycheck(float smallx, float largex, float smallz, float largez)
{
	//this function checks if the camera is close to a side of the object
	bool result = false;
	if ((camera.position.x >= smallx - 2.f) && (camera.position.x <= smallx) && (camera.position.z >= smallz) && (camera.position.z <= largez)){ result = true; }
	if ((camera.position.x <= largex + 2.f) && (camera.position.x >= largex) && (camera.position.z >= smallz) && (camera.position.z <= largez)){ result = true; }
	if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z >= smallz - 2.f) && (camera.position.z <= smallz)){ result = true; }
	if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z <= largez + 2.f) && (camera.position.z >= largez)){ result = true; }
	return result;
}

bool Tools::WithinArea(float smallx, float largex, float smallz, float largez)
{//checks if camera is within a certain area of the room.
	if ((camera.position.x > smallx)
		&&
		(camera.position.x < largex)
		&&
		(camera.position.z > smallz)
		&&
		(camera.position.z < largez)
		)
	{
		return true;
	}
	return false;
}

bool Tools::Interacting(float smallx, float largex, float smallz, float largez)
{
	if (proximitycheck(smallx, largex, smallz, largez) == true && Application::IsKeyPressed('E'))
	{
		return true;
	}
	return false;
}

void Tools::Collision(float smallx, float largex, float smallz, float largez)
{
	if ((camera.position.x > smallx) && (camera.position.x<largex) && (camera.position.z > smallz) && (camera.position.z<smallz + 3.f)){ camera.position.z = smallz; }
	if ((camera.position.x > smallx) && (camera.position.x<largex) && (camera.position.z < largez) && (camera.position.z>largez - 3.f)){ camera.position.z = largez; }
	if ((camera.position.z > smallz) && (camera.position.z<largez) && (camera.position.x > smallx) && (camera.position.x<smallx + 3.f)){ camera.position.x = smallx; }
	if ((camera.position.z > smallz) && (camera.position.z<largez) && (camera.position.x < largex) && (camera.position.x>largex - 3.f)){ camera.position.x = largex; }
	//accounts for possible velocity of objects and clipping through camera.
}