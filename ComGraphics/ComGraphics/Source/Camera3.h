#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"

class Camera3 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view;
	Vector3 right;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void HumanControl();
	virtual void Update(double dt);
	virtual void Reset();

	float rotationX;
	float rotationY;
	void CameraRotation(double dt, float CAMERASPEED);
	float MarginofError = 5.f;
};

#endif