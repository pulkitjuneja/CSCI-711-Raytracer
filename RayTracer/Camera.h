#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"
#include <glm.hpp>

class Camera
{
    glm::vec3 origin;
    glm::vec3 lowerLeftCorner;
    float width;
    float height;
    glm::vec3 horizontal;
    glm::vec3 vertical;

public:
    Camera(float fov, float aspect);
    Ray getCameraRay(float x, float y);
    // keepin gthis a seperate function so user can move the camera as and when required
    void setPositionAndRotation(glm::vec3 worldPosition, glm::vec3 target);
    glm::vec3 getPosition() { return origin; }
};

#endif