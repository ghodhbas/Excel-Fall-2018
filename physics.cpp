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
    //calculate new position
          float hnew = sphere.GetY() + sphere.GetVelocityY() * dt - 0.5 * gravity * dt *dt;
          float xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
          float znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
          if(hnew< sphere.GetRadius())
          {
            sphere.SetY(sphere.GetRadius());
          }

    //sphere in motion
    if( sphere.GetHMax() > sphere.GetHStop())
    {
        //check if the sphere is in free fall mode
        if(sphere.GetState())
        {
        //calculate new position
           hnew = sphere.GetY() + sphere.GetVelocityY() * dt - 0.5 * gravity * dt *dt;
           xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
           znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
          //collision with floor
          if(hnew< sphere.GetRadius())
          {
            sphere.SetTime(sphere.GetTLast() + 2 * sqrt(2*sphere.GetHMax()/gravity));
            sphere.SetState(false);
            sphere.SetTLast(sphere.GetTime() + sphere.GetTau());
            sphere.SetY(sphere.GetRadius());
          }else{
            sphere.SetTime(sphere.GetTime() + dt);
            sphere.SetVelocity(glm::vec3(sphere.GetVelocityX(),sphere.GetVelocityY() - gravity * dt,sphere.GetVelocityZ()));
            sphere.SetPosition(glm::vec3(xnew,hnew,znew));
          }
        }else{
            sphere.SetTime(sphere.GetTime()+sphere.GetTau());
            sphere.SetVMax(sphere.GetVMax() * sphere.GetRho());
            sphere.SetVelocity(glm::vec3(sphere.GetVelocityX(),sphere.GetVMax(),sphere.GetVelocityZ()));
            sphere.SetState(true);
            sphere.SetY(sphere.GetRadius());
        }
        sphere.SetHmax(0.5f * sphere.GetVMax()*sphere.GetVMax()/gravity);

        return;
    }

    glm::vec3 v(0,0,0);
    sphere.SetVelocity(v);

}

