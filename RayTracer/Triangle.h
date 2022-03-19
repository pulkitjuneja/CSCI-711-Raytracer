#pragma once 

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Global.h"
#include "Vector3.h"
#include "Renderable.h"
#include "Ray.h"

struct Vertex {
	Vector3f position;
	// replace this with Vector 2 
	Vector3f texCoords;

	Vertex() = default;
	Vertex(Vector3f position, Vector3f texCoords);
};

class Triangle : public Renderable {
public:
	Vertex V0;
	Vertex V1;
	Vertex V2;

	Triangle(Vertex v0, Vertex v1, Vertex v2, Material material);
	virtual bool intersects(Ray& ray, HitData& rec);
	virtual void getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal);
};

#endif // !TRIANGLE_H
