#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>
#include <math.h>
#include "plane.h"
# include "asa109.hpp"
#include <random>

class Sphere
{
    public:
        Sphere(glm::vec3 position, float mass, float radius);

        virtual ~Sphere();

        bool DetectCollision(Plane& plane);
        void CollisionResponse(Plane& plane);

        bool DetectCollision(Sphere& other);
        void CollisionResponse(Sphere& other);

        /*Getters*/
        float GetX(){return position.x;}
        float GetY(){return position.y;}
        float GetZ(){return position.z;}
        glm::vec3 GetPosition(){return position;}
        glm::vec3 GetVelocity(){return velocity;}
        float GetVelocityX(){return velocity.x;}
        float GetVelocityZ(){return velocity.z;}
        float GetVelocityY(){return velocity.y;}
        float GetRadius(){return radius;}
        float GetMass(){return mass;}
        float GetFix(){return fix;}


        float GetRho(){return rho;}
        float GetVolume(){return volume;}
        float GetElasticity(){return pE;}

        /*Setters*/
        void SetX(float x){position.x = x;}
        void SetY(float y){position.y = y;}
        void SetZ(float z){position.z = z;}
        void SetPosition(glm::vec3 pos){this->position = pos;}
        void SetVelocity(glm::vec3 v){this->velocity = v;}
        void SetVelocityY(float vY){this->velocity.y = vY;}
        void SetVelocityX(float vX){this->velocity.x = vX;}
        void SetVelocityZ(float vZ){this->velocity.z = vZ;}
        void SetRadius(float radius){this->radius=radius;}
        void SetFix(){this->fix=true;}


private:
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(0.f,0.f,0.f);
    float mass;
    float radius;
    float volume;
    //bounce physics
    float rho = 0.1f; //restituion coeff
    //particle elasticity
    float pE= 0.6f;
    bool fix = false;

};

#endif // SPHERE_H
