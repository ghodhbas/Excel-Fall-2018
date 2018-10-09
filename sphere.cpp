#include "sphere.h"
#include <iostream>
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

bool Sphere::DetectCollision(Plane& plane)
{
    float distanceCenterFromPlane = fabs(glm::dot(plane.GetNormal(), GetPosition()) + plane.GetD());
    float distanceFromPlane = distanceCenterFromPlane - GetRadius();
    distanceFromPlane =  roundf(distanceFromPlane * 100) / 100;
     if(distanceFromPlane<=0.00f)
    {
        return true;
    }
    return false;
}

void Sphere::CollisionResponse(Plane& plane)
{
    //collision distance
    float distanceCenterFromPlane = fabs(glm::dot(plane.GetNormal(), position) + plane.GetD());
    float distanceFromPlane = fabs(distanceCenterFromPlane - GetRadius());
    distanceFromPlane =  roundf(distanceFromPlane * 100) / 100;
    //update position speed and energy lost
    glm::vec3 prevPos = GetPosition();
    SetPosition(GetPosition()+ plane.GetNormal() * distanceFromPlane);
    //stable
    if(prevPos != GetPosition()){
        SetHmax(GetHMax()/9);
        SetTLast(GetTime() + GetTau());
        SetVelocity(glm::reflect(GetVelocity(),plane.GetNormal()) * GetRho());
    }

}
