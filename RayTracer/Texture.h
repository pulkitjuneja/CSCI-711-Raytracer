#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector3.h"

class Texture {
public:
	virtual Vector3f value(float u, float v) = 0;
};

class SolidTexture : public Texture {
	Vector3f color;
public:
	SolidTexture(Vector3f color);
	virtual Vector3f value(float u, float v);
};

class CheckeredTexture : public Texture {
	float boxResolution;
	Vector3f color1;
	Vector3f color2;
public:
	CheckeredTexture(Vector3f color1, Vector3f color2, float boxSize);
	virtual Vector3f value(float u, float v);
};

#endif // !TEXTURE_H
