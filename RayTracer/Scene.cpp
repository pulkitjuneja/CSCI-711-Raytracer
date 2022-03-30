#include "Scene.h"

Scene::Scene(RenderOptions& options) : camera(createCamera(options)) {
    sceneAmbience = glm::vec3(0.5, 0.7, 1.0);
}

void Scene::add(Renderable* object)
{
    sceneObjects.push_back(object);
}

void Scene::addPointLight(glm::vec3 position, glm::vec3 color, float intensity)
{
    pointLights.push_back(PointLight(position, color, intensity));
}

Camera Scene::createCamera(RenderOptions& options)
{
    return Camera(options.fov, options.aspectRatio);
}

bool Scene::intersects(Ray& ray, HitData& rec)
{
    bool hitAnything = false;
    int count = 0;
    float closestSoFar = 50000.0f;
    for (vector<Renderable*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
    {
        HitData temprec;
        if ((*it)->intersects(ray, temprec))
        {
            if (temprec.t < closestSoFar)
            {
                closestSoFar = temprec.t;
                rec = temprec;
                hitAnything = true;
            }
        }
    }
    return hitAnything;
}