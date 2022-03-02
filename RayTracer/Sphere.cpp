#include "Sphere.h"

bool Sphere::intersects(Ray& ray, HitData& rec)
{
	Vector3f toCenter = center - ray.position;
	float tca = toCenter.dot(ray.direction);
	if (tca < 0)
		return false;
	float d2 = toCenter.lengthSquared() - tca * tca;
	if (d2 > radius * radius)
		return false;
	float thc = sqrt(radius * radius - d2);
	rec.t = tca - thc;
	rec.hitObject = this;
	rec.hitPoint = ray.pointAtParameter(rec.t);
	rec.normal = (ray.pointAtParameter(rec.t) - center);
	rec.normal.normalize();
	rec.tangent = ray.direction.cross(rec.normal);
	rec.tangent.normalize();

	return true;
}

void Sphere::getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal)
{
	normal = (hitPoint - center).normalize();
}