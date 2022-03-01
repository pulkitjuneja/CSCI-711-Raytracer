#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "global.h"
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class Renderable
{
public:
	Material material;

	Renderable(Material material) : material(material) {};
	virtual bool intersects(Ray& ray, HitData& rec) = 0;
	virtual void getSurfaceProperties(Vector3f& hitPoint, Vector3f& normal) {};
};

#endif