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
	float Kr;
	float Ke;

	Material(Texture* texture, float Ks, float Kr, float ke);
};

#endif // !MATERIAL_H
