#include "Assignment3.h"

void Assignment3::moveGhost(double dt)
{
    timeCount += ((float)(dt) * 5);
    if (timeCount >= 1)
    {
        checkTarget();
        timeCount = 0;
    }
    Vector3 start = Vector3(Ghost1X, Ghost1Y, Ghost1Z);
    Vector3 end = Vector3(TargetDetectX, camera.position.y, TargetDetectZ);
    Vector3 toNorm = end - start;
    Vector3 ghost = start;

    float distance = sqrt(Ghost1X * TargetDetectX + Ghost1Y * camera.position.y + TargetDetectZ * Ghost1Z);
    Vector3 direction = toNorm.Normalize();

    ghost += direction * (float)(100 * dt);

    Ghost1X = ghost.x;
    Ghost1Z = ghost.z;
}