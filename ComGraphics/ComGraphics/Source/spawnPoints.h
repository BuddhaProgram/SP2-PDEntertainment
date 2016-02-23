#ifndef spawnpoints_H
#define spawnpoints_H

#include "Camera3.h"

enum class SpawnPoints
{
	SPAWN_DEFAULT,
	SPAWN_LEVEL1A_ROOM1B,
	NUM_SPAWNS
};

void setSpawns();
void spawnLOC();

#endif // !SpawnPoints_H