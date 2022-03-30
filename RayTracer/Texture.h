#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm.hpp>
#include "Perlin.h"
#include <string>

class Texture {
public:
	virtual glm::vec3 value(float u, float v) = 0;
	virtual ~Texture() = default;
};

class SolidTexture : public Texture {
	glm::vec3 color;
public:
	SolidTexture(glm::vec3 color);
	virtual glm::vec3 value(float u, float v);
};

class CheckeredTexture : public Texture {
	float boxResolution;
	PerlinNoise perlin;
	glm::vec3 color1;
	glm::vec3 color2;
public:
	CheckeredTexture(glm::vec3 color1, glm::vec3 color2, float boxSize);
	virtual glm::vec3 value(float u, float v);
};

class ImageTexture : public Texture {
	unsigned char* imageData;
	int width;
	int height;
	int nrComponents;
	int bytesPerScanline;
public:
	ImageTexture(std::string filename);
	virtual glm::vec3 value(float u, float v);
	virtual ~ImageTexture();
};

#endif // !TEXTURE_H
