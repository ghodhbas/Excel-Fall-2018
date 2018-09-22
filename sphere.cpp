#include "sphere.h"

Sphere::Sphere(float x, float y, float z, float radius)
{
    this->position = glm::vec3(x,y,z);
    this->radius = radius;
}

Sphere::~Sphere()
{
    //dtor
}
