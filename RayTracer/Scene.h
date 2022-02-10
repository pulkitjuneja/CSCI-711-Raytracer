#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Renderable.h"
#include "Ray.h"
#include <vector>
#include "Camera.h"
#include "RenderOptions.h"

using namespace std;

class Scene : public Renderable
{
public:
	vector<Renderable*> sceneObjects;
	Camera camera;

	Scene(RenderOptions& options);
	void add(Renderable* object);
	Camera createCamera(RenderOptions& options);
	void setCamera(Camera camera);
	virtual bool intersects(Ray& ray, HitData& rec);
};

#endif