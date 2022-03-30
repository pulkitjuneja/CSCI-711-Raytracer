#include "Triangle.h"

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, Material material) : Renderable(material),
V0(v0), V1(v1), V2(v2) {};

bool Triangle::intersects(Ray& ray, HitData& rec)
{
	glm::vec3 e1 = V1.position - V0.position;
	glm::vec3 e2 = V2.position - V0.position;

	glm::vec3 N = glm::cross(e1, e2);
	N = glm::normalize(N);

	glm::vec3 pVec = glm::cross(ray.direction, e2);
	float det = glm::dot(pVec, e1);

	if (det < 1e-8f) return false;

	float invDet = 1 / det;

	glm::vec3 tvec = ray.position - V0.position;
	float u = glm::dot(tvec, pVec) * invDet;
	if (u < 0 || u > 1) return false;

	glm::vec3 qvec = glm::cross(tvec,e1);
	float v = glm::dot(ray.direction, qvec) * invDet;
	if (v < 0 || u + v > 1) return false;
	float t = glm::dot(e2, qvec) * invDet;

	float w = 1 - u - v;

	glm::vec3 texCoords = V0.texCoords * w + V1.texCoords * u + V2.texCoords * v;

	rec.t = t;
	rec.normal = N;
	rec.hitObject = this;
	rec.texCoords = texCoords;
	rec.hitPoint = ray.pointAtParameter(t);
	rec.tangent = glm::normalize(e2);
	return true;
}

void Triangle::getSurfaceProperties(glm::vec3& hitPoint, glm::vec3& normal)
{
}

Vertex::Vertex(glm::vec3 position, glm::vec3 texCoords)
{
	this->position = position;
	this->texCoords = texCoords;
}
