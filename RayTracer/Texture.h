#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector3.h"
#include "Perlin.h"

class Texture {
public:
	virtual Vector3f value(float u, float v) = 0;
	virtual ~Texture() = default;
};

class SolidTexture : public Texture {
	Vector3f color;
public:
	SolidTexture(Vector3f color);
	virtual Vector3f value(float u, float v);
};

class CheckeredTexture : public Texture {
	float boxResolution;
	PerlinNoise perlin;
	Vector3f color1;
	Vector3f color2;
public:
	CheckeredTexture(Vector3f color1, Vector3f color2, float boxSize);
	virtual Vector3f value(float u, float v);
};

class ImageTexture : public Texture {
	unsigned char* imageData;
	int width;
	int height;
	int nrComponents;
	int bytesPerScanline;
public:
	ImageTexture(std::string filename);
	virtual Vector3f value(float u, float v);
	virtual ~ImageTexture();
};

#endif // !TEXTURE_H
