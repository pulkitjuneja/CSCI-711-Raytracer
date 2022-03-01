#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Renderable.h"
#include "Ray.h"
#include <vector>
#include "Camera.h"
#include "RenderOptions.h"

using namespace std;

#include "Light.h"

class Scene
{
public:
	vector<Renderable*> sceneObjects;
	vector<PointLight> pointLights;
	Camera camera;
	Vector3f sceneAmbience;

	Scene(RenderOptions& options);

	void add(Renderable* object);
	void addPointLight(Vector3f position, Vector3f color, float intensity);

	Camera createCamera(RenderOptions& options);
	void setCamera(Camera camera);
	virtual bool intersects(Ray& ray, HitData& rec);
};

#endif