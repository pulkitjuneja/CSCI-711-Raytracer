
#include "Raytracer.h"
#include "RenderOptions.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "iostream"

using namespace std;

int main()
{
	RenderOptions options;
	options.height = 720;
	options.width = 1280;
	options.fov = 90;
	options.maxDepth = 50;
	options.aspectRatio = (float)options.width / (float)options.height;
	Scene* scene = new Scene(options);
	scene->camera.setPositionAndRotation(Vector3f(4.91, 1.13, 5.907), Vector3f(0, 0, -1));
	scene->addPointLight(Vector3f(4.5, 2.5, 6), Vector3f(1, 1, 1), 1.0f);
	scene->addPointLight(Vector3f(2.5, 1.5, 6), Vector3f(1, 1, 1), 1.0f);

	scene->add(new Sphere(Vector3f(4.4, 1.1f, 3.907), 1, Material(Vector3f(1,0,0), 0.6f, 0.06f, 64)));
	scene->add(new Sphere(Vector3f(6.2, 0.469, 2.73), 1, Material(Vector3f(0, 1, 0), 0.6f, 0.06f, 32)));
	scene->add(new Triangle(Vector3f(2, -1, 0), Vector3f(2, -1, 4), Vector3f(10, -1, 0), Material(Vector3f(1, 1, 1), 0.6f, 0.06f, 64)));
	scene->add(new Triangle(Vector3f(10, -1, 0), Vector3f(2, -1, 4), Vector3f(10, -1, 4), Material(Vector3f(1, 1, 1), 0.6f, 0.06f, 64)));

	RayTracer tracer;
	tracer.setScene(scene);
	tracer.render(&options);
	return 0;
}