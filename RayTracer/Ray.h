#pragma once

#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3f position;
    Vector3f direction;

    Ray() : position(Vector3f(0, 0, 0)), direction(Vector3f(0, 0, 0)) {};
    Ray(Vector3f position, Vector3f direction) : position(position),
        direction(direction) {};

    Vector3f pointAtParameter(float t);
};

class Renderable;

struct HitData
{
    Vector3f hitPoint;
    Vector3f normal;
    Vector3f tangent;
    Vector3f texCoords;
    Renderable* hitObject;
    float t;
    void calculateProperties(Ray& ray);
};


#endif // !RAY_H