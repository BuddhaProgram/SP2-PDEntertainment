 #include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "SceneStart.h"

float regenDelay = 6.f;
extern GLFWwindow* m_window;
extern SceneStart* numScene;
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

	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera3::CameraRotation(double dt, float CAMERASPEED)
{
	int width, height;

	glfwGetWindowSize(m_window, &width, &height);

	double xpos, ypos;

	glfwGetCursorPos(m_window, &xpos, &ypos);
	glfwSetCursorPos(m_window, width / 2.0f, height / 2.0f);
	rotationY -= ((float)xpos - width / 2.0f) / (1.0f / CAMERASPEED);
	rotationX -= ((float)ypos - height / 2.0f) / (1.0f / CAMERASPEED);

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
		
		}

		if (Application::IsKeyPressed('D'))
		{
			position += right;
			
		}

		if (Application::IsKeyPressed('W'))
		{
			float sprintFactor = 1.5f;
			position.x += sin(Math::DegreeToRadian(rotationY));
			position.z += cos(Math::DegreeToRadian(rotationY));

			if (Application::IsKeyPressed(VK_LSHIFT) && Explorer::instance()->stamina != 0)
			{
				position.x += sprintFactor * sin(Math::DegreeToRadian(rotationY));
				position.z += sprintFactor * cos(Math::DegreeToRadian(rotationY));
				Explorer::instance()->stamina -= 1;
			}
		}

		if (Application::IsKeyPressed('S'))
		{
			position.x -= sin(Math::DegreeToRadian(rotationY));
			position.z -= cos(Math::DegreeToRadian(rotationY));
		}
}

void Camera3::Reset()
{
}

void Camera3::Update(double dt)
{ 
	
	HumanControl();
	CameraRotation(dt, 0.2f);

	target = Vector3(
		sin(Math::DegreeToRadian(rotationY)) * cos(Math::DegreeToRadian(rotationX)) + this->position.x,
		sin(Math::DegreeToRadian(rotationX)) + this->position.y,
		cos(Math::DegreeToRadian(rotationX)) * cos(Math::DegreeToRadian(rotationY)) + this->position.z
	);
	view = (target - position).Normalized();
	right = view.Cross(defaultUp);
	//right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();

	static const float CAMERA_SPEED = 50.f;

	if (Explorer::instance()->stamina <= 0)
	{
		Explorer::instance()->stamina = 0;
		if (regenDelay > 0)
		{
			regenDelay -= (float)dt;
		}
		if (regenDelay <= 0)
		{
			Explorer::instance()->stamina += 15 * (float)dt;
		}
	}
	else
	{
		Explorer::instance()->stamina += 15 * (float)dt;
		regenDelay = 6.f;
	}
	if (Explorer::instance()->stamina > 100)
	{
		Explorer::instance()->stamina = 100;
	}

	Reset();
}