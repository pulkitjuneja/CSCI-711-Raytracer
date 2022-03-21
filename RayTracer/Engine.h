#pragma once

#ifndef ENGINE_H
#define Engine_H

#include "RayTracer.h"

class Engine {
protected:
	RayTracer tracer;
	Scene scene;
	vector<Texture*> textures;
	RenderOptions& options;
public:
	Engine(RenderOptions options);
	virtual void init();
	virtual void release();
	void run();
};

#endif // !ENGINE_H
