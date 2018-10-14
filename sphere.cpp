#define _USE_MATH_DEFINES
#include "sphere.h"
#include <iostream>
#include <math.h>
Sphere::Sphere(glm::vec3 position, float mass, float radius)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
    this->h0 = position.y;
    this->hmax = h0;
    this->tLast = -sqrt(2*h0/9.81f);
    this->vmax = sqrt(2 * hmax * 9.81f);
    this->volume = 4/3 * M_PI * radius * radius * radius;
}

Sphere::~Sphere()
{
}

bool Sphere::DetectCollision(Plane& plane)
{
    float distanceCenterFromPlane = fabs(glm::dot(plane.GetNormal(), GetPosition()) + plane.GetD());
    float distanceFromPlane = distanceCenterFromPlane - GetRadius();
    distanceFromPlane =  roundf(distanceFromPlane * 100) / 100;
     if(distanceFromPlane<0.0f)
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


    SetTime(GetTime()+GetTau());
    SetVMax(GetVMax() * GetRho());
    SetVelocity(glm::reflect(GetVelocity(),plane.GetNormal()) * GetRho());
    SetState(true);
    SetPosition(GetPosition()+ plane.GetNormal() * distanceFromPlane);

}


bool Sphere::DetectCollision(Sphere& other)
{
    float radiusDistance = this->GetRadius() + other.GetRadius();
	float centerDistance = glm::distance(other.GetPosition(), this->GetPosition());
	if(centerDistance <radiusDistance)
	{
        return true;
	}
	return false;
}

void Sphere::CollisionResponse(Sphere& other)
{
    //data
    float radiusDistance = this->GetRadius() + other.GetRadius();
    float centerDistance = glm::distance(other.GetPosition(), this->GetPosition());
    float distance = fabs(centerDistance - radiusDistance);
    //direction of reflections
	glm::vec3 direction = glm::normalize(other.GetPosition() - this->GetPosition());
    glm::vec3 otherdirection = glm::normalize(this->GetPosition() - other.GetPosition());
    //new velocities

    SetVelocity(glm::reflect(GetVelocity(), otherdirection) * (1/GetMass()) / 2.f);
    other.SetVelocity(glm::reflect(other.GetVelocity(),direction) * (1/other.GetMass()) / 2.f);

    //position adjustment
    if(this->GetY() == this->GetRadius()){
         other.SetPosition(other.GetPosition()+ distance * direction);
         return;
    }
    this->SetPosition(this->GetPosition()- distance * direction * 0.5f);
    other.SetPosition(other.GetPosition()+ distance * direction * 0.5f);
    if(this->GetY() < this->GetRadius()){
        glm::vec3 n(0.f,1.f,0.f);
        this->SetVelocity(glm::reflect(direction,n) * other.GetMass() /2.f);
        this->SetY(this->GetRadius());
    }

}
