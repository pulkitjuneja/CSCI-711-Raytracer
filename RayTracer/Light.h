#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>

struct Light {
	glm::vec3 color;
	float intensity;
};

struct PointLight : Light {
	glm::vec3 position;

	PointLight(glm::vec3 position, glm::vec3 color, float intensity) {
		this->position = position;
		this->intensity = intensity;
		this->color = color;
	}
};

#endif // !LIGHT_H
