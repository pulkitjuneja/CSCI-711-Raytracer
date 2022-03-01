#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h" 

struct Light {
	Vector3f color;
	float intensity;
};

struct PointLight : Light {
	Vector3f position;

	PointLight(Vector3f position, Vector3f color, float intensity) {
		this->position = position;
		this->intensity = intensity;
		this->color = color;
	}
};

#endif // !LIGHT_H
