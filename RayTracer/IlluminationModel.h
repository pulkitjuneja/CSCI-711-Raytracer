#pragma once


#ifndef ILLUMINATION_MODEL
#define ILLUMINATION_MODEL

#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"

class IlluminationModel {
public:
	virtual Vector3f calculateLIghting(const HitData& record, PointLight& pointLight,
		Material& material, Camera& camera) = 0;
};

class BlinnPhong : IlluminationModel {
public:
	virtual Vector3f calculateLIghting(const HitData& record, PointLight& pointLight,
		Material& material, Camera& camera);
};

class AshikhmanShirley : IlluminationModel {
	virtual Vector3f calculateLIghting(const HitData& record, PointLight& pointLight,
		Material& material, Camera& camera);
};

#endif // !ILLUMINATION_MODEL
