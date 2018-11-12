#define _USE_MATH_DEFINES
#include "sphere.h"
#include <iostream>
#include <math.h>

/*****************Constructor***********************************/
Sphere::Sphere(glm::vec3 position, float mass, float radius)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
    this->volume = 4/3 * M_PI * radius * radius * radius;
}
Sphere::~Sphere()
{
}

/*****************COLLISION WITH PLANES / CONE***********************************/
bool Sphere::DetectCollision(Plane& plane)
{
    float distanceCenterFromPlane = fabs(glm::dot(plane.GetNormal(), GetPosition()) + plane.GetD());
    float distanceFromPlane = distanceCenterFromPlane - GetRadius();
    //distanceFromPlane =  roundf(distanceFromPlane * 100) / 100;
     if(distanceFromPlane<=0.0f)
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
    glm::vec3 newDir = GetVelocity() - 2 * glm::dot(GetVelocity(),plane.GetNormal()) * plane.GetNormal();
    SetVelocity(newDir * GetRho());
    SetPosition(GetPosition() + plane.GetNormal() * distanceFromPlane);

    if(glm::length(GetVelocity()) < 0.5f){
        SetVelocity(glm::vec3(0.f,0.f,0.f));
    }

}

/*****************COLLISION WITH SPHERES***********************************/
bool Sphere::DetectCollision(Sphere& other)
{
    float radiusDistance = this->GetRadius() + other.GetRadius();
	float centerDistance = glm::distance(other.GetPosition(), this->GetPosition());
	if(centerDistance < radiusDistance)
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
    glm::vec3 direction = glm::normalize(this->GetPosition() - other.GetPosition());
    //
    float a1 = glm::dot(this->GetVelocity(),direction);
    float a2 = glm::dot(other.GetVelocity(),direction);
    float optimizedP = (2.0 * (a1 - a2)) / (this->GetMass() + other.GetMass());
    // Calculate v1', the new movement vector of Sphere 1
    glm::vec3 v1New = this->GetVelocity() - optimizedP * other.GetMass() * direction;
    // Calculate v1', the new movement vector of Sphere2
    glm::vec3 v2New = other.GetVelocity() + optimizedP * this->GetMass() * direction;

    this->SetVelocity(v1New * this->GetElasticity());
    other.SetVelocity(v2New * other.GetElasticity());



        float mcoeff = this->GetMass()/other.GetMass();
        if(mcoeff>1)
        {
            mcoeff = other.GetMass()/this->GetMass();
            this->SetPosition(this->GetPosition()+ direction * distance *  mcoeff);
            other.SetPosition(other.GetPosition()- direction * distance * (1-mcoeff));
        }else if(mcoeff==1){
            mcoeff = 0.5f;
            this->SetPosition(this->GetPosition()+ direction * distance *  mcoeff);
            other.SetPosition(other.GetPosition()- direction * distance * mcoeff);
        }else{
            this->SetPosition(this->GetPosition()+ direction * distance *  (1.f-mcoeff));
            other.SetPosition(other.GetPosition()- direction * distance * mcoeff);
        }


}
