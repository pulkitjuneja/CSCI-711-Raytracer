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
	glm::vec3 sceneAmbience;

	Scene(RenderOptions& options);

	void add(Renderable* object);
	void addPointLight(glm::vec3 position, glm::vec3 color, float intensity);

	Camera createCamera(RenderOptions& options);
	void setCamera(Camera camera);
	virtual bool intersects(Ray& ray, HitData& rec);
};

#endif