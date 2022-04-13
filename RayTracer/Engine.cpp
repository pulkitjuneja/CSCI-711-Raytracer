#include "Engine.h"
#include "Triangle.h"
#include "Sphere.h"

Engine::Engine(RenderOptions options): options(options), scene(options){}

void Engine::init()
{
	scene.camera.setPositionAndRotation(glm::vec3(4.51, 1.13, 5.907), glm::vec3(0, 0, -1));
	scene.addPointLight(glm::vec3(4.7, 2.7, 6), glm::vec3(1, 1, 1), 1.0f);

	Vertex v1(glm::vec3(2, -1, 4.8), glm::vec3(1, 1, 1));
	Vertex v2(glm::vec3(10, -1, 4.8), glm::vec3(1, 0, 0));
	Vertex v3(glm::vec3(2, -1, -1), glm::vec3(0, 1, 0));
	Vertex v4(glm::vec3(10, -1, -1), glm::vec3(1, 1, 0));

	Texture* redTexture = new SolidTexture(glm::vec3(0, 0, 0));
	Texture* greenTexture = new SolidTexture(glm::vec3(0, 1, 0));
	Texture* CheckTexture = new CheckeredTexture(glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), 32);

	Sphere* big = new Sphere(glm::vec3(4.5, 1.0f, 3.907), 1, Material(redTexture, 0.3, 0.4f, 0.6f, 64));
	big->material.refractiveIndex = 0.97f;
	scene.add(big);
	scene.add(new Sphere(glm::vec3(6.2, 0.469, 2.73), 1, Material(greenTexture, 0.8f, 1.0f, 0.0f, 32)));
	scene.add(new Triangle(v1, v2, v3, Material(CheckTexture, 0.2f, 0.0f, 0.0f, 32)));
	scene.add(new Triangle(v3, v2, v4, Material(CheckTexture, 0.2f, 0.0f, 0.0f, 32)));
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


