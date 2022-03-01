#pragma once 

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"

class Material {
public:
	Vector3f diffuse;
	float Ks;
	float Kd;
	float Ka;
	float Ke;

	Material(Vector3f diffuse, float Ks, float Ka, float ke);
};

#endif // !MATERIAL_H
