#include "Texture.h"
#include <bitset>

SolidTexture::SolidTexture(Vector3f color)
{
	this->color = color;
}

Vector3f SolidTexture::value(float u, float v)
{
	return color;
}

CheckeredTexture::CheckeredTexture(Vector3f color1, Vector3f color2, float boxResolution)
{
	this->color1 = color1;
	this->color2 = color2;
	this->boxResolution = boxResolution;
}

Vector3f CheckeredTexture::value(float u, float v)
{
	//float noise = perlin.ValueNoise_2D(u * 16, v * 16);

	//std::bitset<2> checkBits;
	//checkBits.set(0, ((int)floor((u + noise) * boxResolution)) % 2 == 0);
	//checkBits.set(1, ((int)floor((v + noise) * boxResolution)) % 2 == 0);

	std::bitset<2> checkBits;
	checkBits.set(0, ((int)floor(u * boxResolution)) % 2 == 0);
	checkBits.set(1, ((int)floor(v * boxResolution)) % 2 == 0);

	//basically checking if they are both even or both odd
	if (!(checkBits[0] ^ checkBits[1])) {
		return color1;
	}

	return color2;
}
