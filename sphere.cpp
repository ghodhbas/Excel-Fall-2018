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



    //SetTime(GetTime()+GetTau());
    //SetVMax(GetVMax() * GetRho());
    SetVelocity(glm::reflect(GetVelocity(),plane.GetNormal()) * GetRho());
    //SetState(true);
    SetPosition(GetPosition()+ plane.GetNormal() * distanceFromPlane);
//    if(GetY()>GetRadius())
//        SetVelocity(glm::reflect(GetVelocity(),plane.GetNormal()))
//

    if( (distanceFromPlane + glm::length(GetVelocity()) )== 0 )
        SetVMax(GetVMax()/GetRho());

}


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
    //direction of reflections
	glm::vec3 direction = glm::normalize(other.GetPosition() - this->GetPosition());
    glm::vec3 otherdirection = glm::normalize(this->GetPosition() - other.GetPosition());

    //mass coeff
    float mcoeff = this->GetMass()/other.GetMass();
    if(mcoeff>1)
    {
        mcoeff = other.GetMass()/this->GetMass();
        this->SetPosition(this->GetPosition()- direction * distance *  mcoeff);
        other.SetPosition(other.GetPosition()+ direction * distance * (1-mcoeff));
    }else if(mcoeff==1){
        mcoeff = 0.5f;
        this->SetPosition(this->GetPosition()- direction * distance *  mcoeff);
        other.SetPosition(other.GetPosition()+ direction * distance * mcoeff);
    }else{
        this->SetPosition(this->GetPosition()- direction * distance *  (1.f-mcoeff));
        other.SetPosition(other.GetPosition()+ direction * distance * mcoeff);
    }

    //two moving spheres
    if(glm::length(this->GetVelocity())!=0 && glm::length(other.GetVelocity())!= 0)
    {
        //new v for first sphere using momentum and energy
        float Vnew1x = (this->GetVelocityX() * (this->GetMass()-other.GetMass()) + (2* other.GetMass() * other.GetVelocityX())) / (this->GetMass() + other.GetMass());
        float Vnew1y = -((this->GetVelocityY() * (this->GetMass()-other.GetMass()) + (2* other.GetMass() * other.GetVelocityY())) / (this->GetMass() + other.GetMass()));
        float Vnew1z = (this->GetVelocityZ() * (this->GetMass()-other.GetMass()) + (2* other.GetMass() * other.GetVelocityZ())) / (this->GetMass() + other.GetMass());
        glm::vec3 v1New(Vnew1x,Vnew1y,Vnew1z);

        //new v for 2nd sphere
        float Vnew2x = (other.GetVelocityX() * (other.GetMass()-this->GetMass()) + (2* this->GetMass() * this->GetVelocityX())) / (this->GetMass() + other.GetMass());
        float Vnew2y = (other.GetVelocityY() * (other.GetMass()-this->GetMass()) + (2* this->GetMass() * this->GetVelocityY())) / (this->GetMass() + other.GetMass());
        float Vnew2z = (other.GetVelocityZ() * (other.GetMass()-this->GetMass()) + (2* this->GetMass() * this->GetVelocityZ())) / (this->GetMass() + other.GetMass());
        glm::vec3 v2New(Vnew2x,Vnew2y,Vnew2z);

        //this->SetVelocity(glm::normalize(glm::reflect(GetVelocity(), otherdirection))   *  glm::length(v1New) * this->GetElasticity());
        //other.SetVelocity(glm::normalize(glm::reflect(other.GetVelocity(), direction))   *  glm::length(v2New) * other.GetElasticity()  );

        //update speeds
        this->SetVelocityX(Vnew1x * this->GetElasticity());
        this->SetVelocityY(Vnew1y * this->GetElasticity());
        this->SetVelocityZ(Vnew1z * this->GetElasticity());

        other.SetVelocityX(Vnew2x * other.GetElasticity());
        other.SetVelocityY(Vnew2y * other.GetElasticity());
        other.SetVelocityZ(Vnew2z * other.GetElasticity());

        //this->SetVelocity(glm::reflect(GetVelocity(), otherdirection) *   (1/GetRadius())   );
        //other.SetVelocity(glm::reflect(other.GetVelocity(),direction) *  (1/GetRadius())  );
    }else if(glm::length(this->GetVelocity())==0 && glm::length(other.GetVelocity())!= 0)
    {
        this->SetVelocity(otherdirection  * glm::length(other.GetVelocity()) * this->GetElasticity()  );
        other.SetVelocity(glm::reflect(other.GetVelocity(),direction) * other.GetElasticity()  );
    }else if(glm::length(other.GetVelocity())==0 && glm::length(this->GetVelocity())!=0)
    {
       other.SetVelocity(direction  * glm::length(this->GetVelocity()) * other.GetElasticity()  );
       this->SetVelocity(glm::reflect(GetVelocity(), otherdirection)* this->GetElasticity() );
    }

    //collision with floor
    if(this->GetY() < this->GetRadius()){
        glm::vec3 n(0.f,1.f,0.f);
        this->SetVelocity(glm::reflect(direction,n)* glm::length(other.GetVelocity()) * this->GetRho());
        this->SetY(this->GetRadius());
    }
    if(other.GetY()<other.GetRadius())
    {
        glm::vec3 n(0.f,1.f,0.f);
        other.SetVelocity(glm::reflect(otherdirection,n) * glm::length(other.GetVelocity()) * other.GetRho());
        other.SetY(other.GetRadius());
    }


}
