#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "Assignment3.h"

extern GLFWwindow* m_window;

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	rotationX = 0;
	rotationY = 0;
	targetZoom = 200.0f;

	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera3::CameraRotation(double dt, float CAMERASPEED)
{
	int Width;
	int Height;

	glfwGetWindowSize(m_window, &Width, &Height);

	POINT p;
	GetCursorPos(&p);
	SetCursorPos(Width / 2.0f, Height / 2.0f);

	rotationY -= (p.x - Width / 2.0f) / (1.0f / CAMERASPEED);
	rotationX -= (p.y - Height / 2.0f) / (1.0f / CAMERASPEED);

	if (rotationX > 50.0f)
	{
		rotationX = 50.0f;
	}

	else if (rotationX < -50.0f)
	{
		rotationX = -50.0f;
	}

	if (rotationY > 360.0f || rotationY < -360.0f)
	{
		rotationY = 0;
	}

	target = Vector3(
		sin(Math::DegreeToRadian(rotationY)) * cos(Math::DegreeToRadian(rotationX)) + this->position.x, 
		sin(Math::DegreeToRadian(rotationX)) + this->position.y, 
		cos(Math::DegreeToRadian(rotationX)) * cos(Math::DegreeToRadian(rotationY)) + this->position.z
		);
}

void Camera3::HumanControl()
{
	view = (target - position).Normalized();

	if (Application::IsKeyPressed('A'))
	{
		position -= right;
		target -= right;
	}

	if (Application::IsKeyPressed('D'))
	{
		position += right;
		target += right;
	}

	if (Application::IsKeyPressed('W'))
	{
		position.x += sin(Math::DegreeToRadian(rotationY));
		position.z += cos(Math::DegreeToRadian(rotationY));
	}

	if (Application::IsKeyPressed('S'))
	{
		position.x -= sin(Math::DegreeToRadian(rotationY));
		position.z -= cos(Math::DegreeToRadian(rotationY));
	}
}

void Camera3::Reset()
{
	if (Application::IsKeyPressed('R'))
	{
		position = defaultPosition;
		target = rotationX = rotationY = 0;
		up = defaultUp;

		rotationX = 0;
		rotationY = 0;
		targetZoom = 200.0f;
	}
}

void Camera3::Update(double dt)
{ 
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();

	static const float CAMERA_SPEED = 50.f;

	HumanControl();
	CameraRotation(dt, 0.2f);

	Reset();
}