#pragma once

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Vector3.h"
#include "global.h"
#include "Ray.h"
#include "RenderOptions.h"
#include "Scene.h"
#include <atomic>
#include <thread>
#include "IlluminationModel.h"

#define PI 3.14159265

using namespace std;

class RayTracer
{
protected:
	int MAX_DEPTH;
	Scene* scene;
	atomic<int> rowsRendered{ 0 };
	atomic<int> nextRow{ 0 };

	BlinnPhong blinnPhong;
	Vector3f trace(Ray& ray, int depth);
	Vector3f reflect(Vector3f& S, Vector3f& N);

	template <typename T>
	T clamp(const T& value, const T& low, const T& high)
	{
		return value < low ? low : (value > high ? high : value);
	}

public:
	void render(RenderOptions* options);
	void renderRow(RenderOptions* options, Vector3f* frameBuffer);
	Vector3f calculateLighting(const HitData& record);
	void setScene(Scene* scene);
	void writeToImgae(Vector3f* frameBuffer, RenderOptions* options);
};

#endif