#ifndef PHYSICS_H
#define PHYSICS_H
#include <glm/glm.hpp>
#include "sphere.h"

class Physics
{
    public:
        Physics(float gravity);
        virtual ~Physics();


        void ApplyGravity(Sphere* sphere);

        glm::vec3 GetAccelarion(){return acceleration;}

        void SetAcceleration(glm::vec3 acc){this->acceleration = acc;}

    protected:

    private:
    float gravity = 9.81f;
    glm::vec3 acceleration = glm::vec3(0.f,-gravity,0.f);

};

#endif // PHYSICS_H
