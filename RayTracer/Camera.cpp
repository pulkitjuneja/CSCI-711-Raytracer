#include "Camera.h"

#define PI 3.14159265

Camera::Camera(float fov, float aspect)
{
    float theta = fov * (PI / 180);
    float halfHeight = tan(theta / 2);
    //lowerLeftCorner = glm::vec3(-halfWidth, -halfHeight, -1);
    height = 2 * halfHeight;
    width = height * aspect;
    origin = glm::vec3(0, 0, 0);
}

Ray Camera::getCameraRay(float x, float y)
{
    glm::vec3 dir(lowerLeftCorner + horizontal * x + vertical * y - origin);
    dir = glm::normalize(dir);
    return Ray(origin, dir);
}

void Camera::setPositionAndRotation(glm::vec3 worldPosition, glm::vec3 target)
{
    origin = worldPosition;
    glm::vec3 worldUp(0, 1, 0);

    glm::vec3 dir = glm::normalize(-target);
    glm::vec3 right = glm::normalize(glm::cross(worldUp, dir));
    glm::vec3 up = glm::cross(dir, right);

    horizontal = right * width;
    vertical = up* height;

    lowerLeftCorner = origin - (horizontal / 2.0f) - (vertical / 2.0f) - dir;
}
