#include "Camera.h"

#define PI 3.14159265

Camera::Camera(float fov, float aspect)
{
    float theta = fov * (PI / 180);
    float halfHeight = tan(theta / 2);
    //lowerLeftCorner = Vector3f(-halfWidth, -halfHeight, -1);
    height = 2 * halfHeight;
    width = height * aspect;
    origin = Vector3f(0, 0, 0);
}

Ray Camera::getCameraRay(float x, float y)
{
    Vector3f dir(lowerLeftCorner + horizontal * x + vertical * y - origin);
    dir = dir.normalize();
    return Ray(origin, dir);
}

void Camera::setPositionAndRotation(Vector3f worldPosition, Vector3f target)
{
    origin = worldPosition;
    Vector3f worldUp(0, 1, 0);

    Vector3f dir = -target.normalize();
    Vector3f right = worldUp.cross(dir).normalize();
    Vector3f up = dir.cross(right);

    horizontal = right * width;
    vertical = up* height;

    lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - dir;
}
