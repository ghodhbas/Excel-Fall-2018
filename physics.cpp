#include "physics.h"

Physics::Physics(float gravity)
{
   this->gravity = gravity;
}

Physics::~Physics()
{
    //dtor
}

 void Physics::ApplyGravity(Sphere* sphere)
 {
    //update vilocity
    sphere->SetPosition(sphere->GetPosition() + acceleration * 0.5f * sphere->GetTime() * sphere->GetTime());
    sphere->SetTime(sphere->GetTime() + 0.001f);
 }
