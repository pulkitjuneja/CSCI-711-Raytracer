#include "Sphere.h"

bool Sphere::intersects(Ray& ray, HitData& rec)
{
	glm::vec3 toCenter = center - ray.position;
	float tca = glm::dot(toCenter, ray.direction);
	if (tca < 0)
		return false;
	float d2 = glm::dot(toCenter, toCenter) - tca * tca;
	if (d2 > radius * radius)
		return false;
	float thc = sqrt(radius * radius - d2);
	rec.t = tca - thc;
	rec.hitObject = this;
	rec.hitPoint = ray.pointAtParameter(rec.t);
	rec.normal = glm::normalize(ray.pointAtParameter(rec.t) - center);
	rec.tangent = glm::normalize(glm::cross(ray.direction, rec.normal));

	return true;
}

void Sphere::getSurfaceProperties(glm::vec3& hitPoint, glm::vec3& normal)
{
	normal = glm::normalize(hitPoint - center);
}