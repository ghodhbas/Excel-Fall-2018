#ifndef PHYSICS_H
#define PHYSICS_H
#include <glm/glm.hpp>
#include <vector>
#include <math.h>
#include "plane.h"
#include "sphere.h"

class Physics
{
public:
        Physics(float gravity);
        virtual ~Physics();
        //timestep
        float dt = 0.1f;
        void ApplyGravity(Sphere& sphere, Plane& rp,Plane& lp,Plane& bp,Plane& fp);

        /*****GETTERS*****/
        float GetGravity(){return gravity;}
        glm::vec3 GetAccelarion(){return acceleration;}
        /*****SETTERS*****/
        void SetAcceleration(glm::vec3 acc){this->acceleration = acc;}
        void SetGravity(float f){this->gravity =f;}

private:
    float gravity = 9.8f;
    glm::vec3 acceleration = glm::vec3(0.f,-gravity,0.f);

};

#endif // PHYSICS_H
