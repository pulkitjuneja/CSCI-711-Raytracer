#include "Triangle.h"

Triangle::Triangle(Vector3f v0, Vector3f v1, Vector3f v2)
{
	V0 = v0;
	V1 = v1;
	V2 = v2;
}

bool Triangle::intersects(Ray& ray, HitData& rec)
{
	Vector3f e1 = V1 - V0;
	Vector3f e2 = V2 - V0;

	Vector3f N = e1.cross(e2);
	N = N.normalize();

	float d = N.dot(V0);

	Vector3f pVec = ray.direction.cross(e2);
	float aNum = pVec.dot(e1);

	// Backfacing / nearly parallel, or close to the limit of precision ?
	if (abs(aNum) < 1e-8f) return false;

	Vector3f tvec = ray.position - V0;
	float u = pVec.dot(tvec) / aNum;
	if (u < 0.0f || u > 1.0f) return false;

	Vector3f qVec = tvec.cross(e1);
	float v = qVec.dot(ray.direction) / aNum;
	if (v < 0.0 || u + v > 1.0f) return false;

	float t = qVec.dot(e2) / aNum;
	if (t < 0) return false;

	rec.t = t;
	rec.normal = N;
	return true;
}

void Triangle::getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal)
{
}
