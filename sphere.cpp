#include "sphere.h"

Sphere::Sphere(float x, float y, float z, float mass, float radius)
{
    this->position = glm::vec3(x,y,z);
    this->mass = mass;
    this->radius = radius;
}

Sphere::~Sphere()
{
    //dtor
}
