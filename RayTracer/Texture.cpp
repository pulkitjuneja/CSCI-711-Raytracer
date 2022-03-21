#include "Texture.h"
#include <bitset>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

ImageTexture::ImageTexture(std::string filename)
{
	imageData = stbi_load(filename.c_str(), &width, &height, &nrComponents, nrComponents);
	if (!imageData) {
		std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
		width = height = 0;
	}

	bytesPerScanline = nrComponents * width;
}

Vector3f ImageTexture::value(float u, float v)
{
	if (imageData == nullptr) {
		return Vector3f(0, 1, 1);
	}

	u = std::clamp(u, 0.0f, 1.0f);
	v = 1.0 - std::clamp(v, 0.0f, 1.0f);  // Flip V to image coordinates

	auto i = static_cast<int>(u * width);
	auto j = static_cast<int>(v * height);

	const auto colorScale = 1.0 / 255.0;
	auto pixel = imageData + j * bytesPerScanline + i * nrComponents;

	return Vector3f(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
}

ImageTexture::~ImageTexture()
{
	delete imageData;
}
