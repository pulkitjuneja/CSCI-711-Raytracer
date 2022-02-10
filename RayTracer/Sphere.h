#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "Global.h"
#include "Vector3.h"
#include "Renderable.h"
#include "Ray.h"

class Sphere : public Renderable
{
public:
	float radius;
	Vector3f center;

	Sphere(Vector3f pos, float rad) : center(pos), radius(rad) {}
	virtual bool intersects(Ray& ray, HitData& rec);
	virtual void getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal);
};

#endif