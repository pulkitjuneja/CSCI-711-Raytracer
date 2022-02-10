#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H

#include "Vector3.cpp"

class RenderOptions
{
public:
	int height;
	int width;
	float aspectRatio;
	float fov;
	int maxDepth;
};

#endif