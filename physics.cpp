#include "physics.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

Physics::Physics(float gravity)
{
   this->gravity = gravity;
}

Physics::~Physics()
{
    //dtor
}

void Physics::ApplyGravity(Sphere& sphere)
{
    //sphere in motion
    if( sphere.GetHMax() > sphere.GetHStop())
    {
        //check if the sphere is in free fall mode
        if(sphere.GetState())
        {
        //calculate new position
          float hnew = sphere.GetY() + sphere.GetVelocityY() * dt - 0.5 * 9.81f * dt *dt;
          //collision with floor
          if(hnew< sphere.GetRadius())
          {
            sphere.SetTime(sphere.GetTLast() + 2 * sqrt(2*sphere.GetHMax()/9.81f));
            sphere.SetState(false);
            sphere.SetTLast(sphere.GetTime() + sphere.GetTau());
            sphere.SetY(sphere.GetRadius());
          }else{
            sphere.SetTime(sphere.GetTime() + dt);
            sphere.SetVelocityY(sphere.GetVelocityY() - 9.81f * dt);
            sphere.SetY(hnew);
          }
        }else{
            sphere.SetTime(sphere.GetTime()+sphere.GetTau());
            sphere.SetVMax(sphere.GetVMax() * sphere.GetRho());
            sphere.SetVelocityY(sphere.GetVMax());
            sphere.SetState(true);
            sphere.SetY(sphere.GetRadius());
        }
        sphere.SetHmax(0.5f * sphere.GetVMax()*sphere.GetVMax()/9.81f);
    }

}

void Physics::DetectCollisions(std::vector<Sphere>& SphereContainer, Plane& ground)
{
    //sphere plane collision

}

