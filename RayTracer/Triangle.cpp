#include "Triangle.h"

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, Material material) : Renderable(material),
V0(v0), V1(v1), V2(v2) {};

bool Triangle::intersects(Ray& ray, HitData& rec)
{
	Vector3f e1 = V1.position - V0.position;
	Vector3f e2 = V2.position - V0.position;

	Vector3f N = e1.cross(e2);
	N = N.normalize();

	Vector3f pVec = ray.direction.cross(e2);
	float det = pVec.dot(e1);

	if (det < 1e-8f) return false;

	float invDet = 1 / det;

	Vector3f tvec = ray.position - V0.position;
	float u = tvec.dot(pVec) * invDet;
	if (u < 0 || u > 1) return false;

	Vector3f qvec = tvec.cross(e1);
	float v = ray.direction.dot(qvec) * invDet;
	if (v < 0 || u + v > 1) return false;
	float t = e2.dot(qvec) * invDet;

	float w = 1 - u - v;

	Vector3f texCoords = V0.texCoords * w + V1.texCoords * u + V2.texCoords * v;

	rec.t = t;
	rec.normal = N;
	rec.hitObject = this;
	rec.texCoords = texCoords;
	rec.hitPoint = ray.pointAtParameter(t);
	rec.tangent = e2;
	rec.tangent.normalize();
	return true;
}

void Triangle::getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal)
{
}

Vertex::Vertex(Vector3f position, Vector3f texCoords)
{
	this->position = position;
	this->texCoords = texCoords;
}
