#include "Ray.h"
#include "Renderable.h"

Vector3f Ray::pointAtParameter(float t)
{
	return position + direction * t;
}

void HitData::calculateProperties(Ray& ray)
{
	hitPoint = ray.pointAtParameter(t);
	hitObject->getSurfaceProperties(hitPoint, normal);
}
