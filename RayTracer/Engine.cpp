#include "Engine.h"
#include "Triangle.h"
#include "Sphere.h"

Engine::Engine(RenderOptions options): options(options), scene(options){}

void Engine::init()
{
	scene.camera.setPositionAndRotation(Vector3f(4.91, 1.13, 5.907), Vector3f(0, 0, -1));
	scene.addPointLight(Vector3f(4.5, 2.5, 6), Vector3f(1, 1, 1), 1.0f);
	scene.addPointLight(Vector3f(2.5, 1.5, 6), Vector3f(1, 1, 1), 1.0f);

	Vertex v1(Vector3f(2, -1, 3.8), Vector3f(0, 0, 0));
	Vertex v2(Vector3f(10, -1, 3.8), Vector3f(1, 0, 0));
	Vertex v3(Vector3f(2, -1, -1), Vector3f(0, 1, 0));
	Vertex v4(Vector3f(10, -1, -1), Vector3f(1, 1, 0));

	Texture* redTexture = new SolidTexture(Vector3f(1, 0, 0));
	Texture* greenTexture = new SolidTexture(Vector3f(0, 1, 0));
	Texture* CheckTexture = new CheckeredTexture(Vector3f(1, 0, 0), Vector3f(1, 1, 0), 32);
	Texture* imageTexture = new ImageTexture("Textures/crate_1.jpg");

	scene.add(new Sphere(Vector3f(4.4, 1.1f, 3.907), 1, Material(redTexture, 0.6f, 0.06f, 64)));
	scene.add(new Sphere(Vector3f(6.2, 0.469, 2.73), 1, Material(greenTexture, 0.6f, 0.06f, 32)));
	scene.add(new Triangle(v1, v2, v3, Material(imageTexture, 0.6f, 0.06f, 64)));
	scene.add(new Triangle(v3, v2, v4, Material(imageTexture, 0.6f, 0.06f, 64)));
}

void Engine::release()
{

}

void Engine::run()
{
	init();
	tracer.setScene(&scene);
	tracer.render(&options);
	release();
}


