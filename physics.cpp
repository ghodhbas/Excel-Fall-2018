#include "physics.h"

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
    //update velocity
    sphere.SetVelocity(sphere.GetVelocity() + acceleration * sphere.GetTime() );
    //update position
    sphere.SetPosition(sphere.GetPosition() + sphere.GetVelocity() * 0.5f * sphere.GetTime());
    //update delta time
    sphere.SetTime(sphere.GetTime() + 0.001f);
}

void Physics::DetectCollisions(std::vector<Sphere>& SphereContainer, Plane& ground)
{
    //sphere plane collision

}

