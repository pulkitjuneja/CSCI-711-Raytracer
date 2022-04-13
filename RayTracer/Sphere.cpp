#include "Sphere.h"

bool Sphere::intersects(Ray& ray, HitData& rec)
{
	//glm::vec3 toCenter = center - ray.position;
	//float tca = glm::dot(toCenter, ray.direction);
	//if (tca < 0)
	//	return false;
	//float d2 = glm::dot(toCenter, toCenter) - tca * tca;
	//if (d2 > radius * radius)
	//	return false;
	//float thc = sqrt(radius * radius - d2);
	//rec.t = tca - thc;
	//rec.hitObject = this;
	//rec.hitPoint = ray.pointAtParameter(rec.t);
	//rec.normal = (rec.hitPoint - center) / radius;
	//rec.tangent = glm::normalize(glm::cross(ray.direction, rec.normal));

	//return true;
	glm::normalize(ray.direction);
	glm::vec3 oc = center - ray.position;
	float a = glm::dot(ray.direction, ray.direction);
	auto rayOrigin = ray.position;
	auto rayDir = ray.direction;
	float b = 2 * (rayDir.x * (rayOrigin.x - center.x) + rayDir.y * (rayOrigin.y - center.y) + rayDir.z * (rayOrigin.z - center.z));
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = (b * b) - (4 * c);

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / 2;

		if (temp > 0)
		{
			rec.t = temp;
			rec.hitPoint = ray.pointAtParameter(temp);
			rec.normal = glm::normalize(rec.hitPoint - center);
			rec.hitObject = this;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / 2;

		if (temp > 0)
		{
			rec.t = temp;
			rec.hitPoint = ray.pointAtParameter(temp);
			rec.normal = glm::normalize(rec.hitPoint - center);
			rec.hitObject = this;
			return true;
		}
	}
	return false;
}

void Sphere::getSurfaceProperties(glm::vec3& hitPoint, glm::vec3& normal)
{
	normal = glm::normalize(hitPoint - center);
}