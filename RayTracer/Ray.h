#pragma once

#ifndef RAY_H
#define RAY_H

#include <glm.hpp>

class Ray {
public:
    glm::vec3 position;
    glm::vec3 direction;

    Ray() : position(glm::vec3(0, 0, 0)), direction(glm::vec3(0, 0, 0)) {};
    Ray(glm::vec3 position, glm::vec3 direction) : position(position),
        direction(direction) {};

    glm::vec3 pointAtParameter(float t);
};

class Renderable;

struct HitData
{
    glm::vec3 hitPoint;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 texCoords;
    Renderable* hitObject;
    float t;
    void calculateProperties(Ray& ray);
};


#endif // !RAY_H