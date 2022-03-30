#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "Global.h"
#include <glm.hpp>
#include "Renderable.h"
#include "Ray.h"

class Sphere : public Renderable
{
public:
	float radius;
	glm::vec3 center;

	Sphere(glm::vec3 pos, float rad, Material material) : center(pos), 
		radius(rad), Renderable(material) {}
	virtual bool intersects(Ray& ray, HitData& rec);
	virtual void getSurfaceProperties(glm::vec3& hitPoint, glm::vec3& normal);
};

#endif