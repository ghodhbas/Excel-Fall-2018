#include "sphere.h"

Sphere::Sphere(glm::vec3 position, float mass, float radius)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
    this->h0 = position.y;
    this->hmax = h0;
    this->tLast = -sqrt(2*h0/9.81f);
    this->vmax = sqrt(2 * hmax * 9.81f);
}

Sphere::~Sphere()
{
}

