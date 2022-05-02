#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H

#include "Vector3.cpp"


enum class ToneMappingOperator {
	Reinhard,
	Ward,
	ALM
};

class RenderOptions
{
public:
	int height;
	int width;
	float aspectRatio;
	float fov;
	int maxDepth;
	ToneMappingOperator toneMappingOperator;
};

#endif