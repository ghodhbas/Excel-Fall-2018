#ifndef PHYSICS_H
#define PHYSICS_H
#include <glm/glm.hpp>
#include <vector>
#include "plane.h"
#include "sphere.h"

class Physics
{
    public:
        Physics(float gravity);
        virtual ~Physics();

        void ApplyGravity(Sphere& sphere);
        void DetectCollisions(std::vector<Sphere>& SphereContainer, Plane& ground);

        glm::vec3 GetAccelarion(){return acceleration;}

        void SetAcceleration(glm::vec3 acc){this->acceleration = acc;}

    protected:

    private:
    float gravity = 9.81f;
    glm::vec3 acceleration = glm::vec3(0.f,-gravity,0.f);

};

#endif // PHYSICS_H
