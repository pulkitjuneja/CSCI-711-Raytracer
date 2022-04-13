#pragma once

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm.hpp>
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
	glm::vec3 trace(Ray& ray, int depth);
	glm::vec3 reflect(glm::vec3& S, glm::vec3& N);
	bool refract(const glm::vec3 direction, const glm::vec3 normal, float niOverNt, glm::vec3& refracted);

	template <typename T>
	T clamp(const T& value, const T& low, const T& high)
	{
		return value < low ? low : (value > high ? high : value);
	}

public:
	void render(RenderOptions* options);
	void renderRow(RenderOptions* options, glm::vec3* frameBuffer);
	glm::vec3 calculateLighting(const HitData& record);
	float Schlick(float cosine, float ref_idx);
	void setScene(Scene* scene);
	void writeToImgae(glm::vec3* frameBuffer, RenderOptions* options);
};

#endif