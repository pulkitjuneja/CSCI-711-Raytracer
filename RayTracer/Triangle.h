#pragma once 

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Global.h"
#include <glm.hpp>
#include "Renderable.h"
#include "Ray.h"

struct Vertex {
	glm::vec3 position;
	// replace this with Vector 2 
	glm::vec3 texCoords;

	Vertex() = default;
	Vertex(glm::vec3 position, glm::vec3 texCoords);
};

class Triangle : public Renderable {
public:
	Vertex V0;
	Vertex V1;
	Vertex V2;

	Triangle(Vertex v0, Vertex v1, Vertex v2, Material material);
	virtual bool intersects(Ray& ray, HitData& rec);
	virtual void getSurfaceProperties(glm::vec3& hitPoint, glm::vec3& normal);
};

#endif // !TRIANGLE_H
