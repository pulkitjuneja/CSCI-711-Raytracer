#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "global.h"
#include "Ray.h"
#include "Material.h"
#include <glm.hpp>

class Renderable
{
public:
	Material material;

	Renderable(Material material) : material(material) {};
	virtual bool intersects(Ray& ray, HitData& rec) = 0;
	virtual void getSurfaceProperties(glm::vec3& hitPoint, glm::vec3& normal) {};
};

#endif