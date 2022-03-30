#pragma once


#ifndef ILLUMINATION_MODEL
#define ILLUMINATION_MODEL

#include <glm.hpp>
#include "Ray.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include "glm.hpp"
#include "vec3.hpp"

class IlluminationModel {
public:
	virtual glm::vec3 calculateLIghting(const HitData& record, PointLight& pointLight,
		Material& material, Camera& camera) = 0;
};

class BlinnPhong : IlluminationModel {
public:
	virtual glm::vec3 calculateLIghting(const HitData& record, PointLight& pointLight,
		Material& material, Camera& camera);
	glm::vec3 ImportanceSample(glm::vec2 Xi, glm::vec3 N, float specExponent);
	glm::vec3 CalculateDiffuseDirection(glm::vec2 Xi, glm::vec3 N);
};

class AshikhmanShirley : IlluminationModel {
	virtual glm::vec3 calculateLIghting(const HitData& record, PointLight& pointLight,
		Material& material, Camera& camera);
};

#endif // !ILLUMINATION_MODEL
