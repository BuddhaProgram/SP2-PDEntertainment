#ifndef SCENE_H
#define SCENE_H

#include "GlobalVariables.h"
#include "Explorer.h"

class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	GlobalVariables Variables;
	ToolUI::ToolType Tool;
};

#endif