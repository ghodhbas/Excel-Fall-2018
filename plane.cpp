#include "plane.h"

/*****************Constructor***********************************/
Plane::Plane(glm::vec3 N, float D)
{
   this->N = N;
   this->D = D;
}
Plane::~Plane()
{
}

/*****************NORMALIZE***********************************/
Plane Plane::Normalized()
{
    this->N = glm::normalize(this->N);
    this->D = D / glm::length(N);
    return Plane(N,D);
}
