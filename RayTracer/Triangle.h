#pragma once 

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Global.h"
#include "Vector3.h"
#include "Renderable.h"
#include "Ray.h"

class Triangle : public Renderable {
public:
	Vector3f V0;
	Vector3f V1;
	Vector3f V2;

	Triangle(Vector3f v0, Vector3f v1, Vector3f v2);
	virtual bool intersects(Ray& ray, HitData& rec);
	virtual void getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal);
};

#endif // !TRIANGLE_H
