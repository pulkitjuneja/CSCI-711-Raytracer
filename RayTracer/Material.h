#pragma once 

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"
#include "Texture.h"

class Material {
public:
	Texture* diffuse;
	float Ks;
	float Kd;
	float Ka;
	float Ke;

	Material(Texture* texture, float Ks, float Ka, float ke);
};

#endif // !MATERIAL_H
