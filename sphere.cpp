#include "sphere.h"

Sphere::Sphere(glm::vec3 position, float mass, float radius)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
}

Sphere::~Sphere()
{
}

bool Sphere::DetectCollision(Plane& plane)
{
    float distanceCenterFromPlane = fabs(glm::dot(plane.GetNormal(), position) + plane.GetD());
    float distanceFromPlane = distanceCenterFromPlane - radius;

    if(distanceFromPlane<0)
    {
        return true;
    }
    return false;
}

