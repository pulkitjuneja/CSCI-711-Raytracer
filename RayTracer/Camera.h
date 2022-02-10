#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

class Camera
{
    Vector3f origin;
    Vector3f lowerLeftCorner;
    float width;
    float height;
    Vector3f horizontal;
    Vector3f vertical;

public:
    Camera(float fov, float aspect);
    Ray getCameraRay(float x, float y);
    // keepin gthis a seperate function so user can move the camera as and when required
    void setPositionAndRotation(Vector3f worldPosition, Vector3f target);
};

#endif