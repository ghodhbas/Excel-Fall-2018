#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>
#include <math.h>
#include "plane.h"
#include "asa109.cpp"
#include <random>

class Sphere
{
    public:
        Sphere(glm::vec3 position, float mass, float radius);

        virtual ~Sphere();

        bool DetectCollision(Plane& plane);


        float GetX(){return position.x;}
        float GetY(){return position.y;}
        float GetZ(){return position.z;}
        glm::vec3 GetPosition(){return position;}
        glm::vec3 GetVelocity(){return velocity;}
        float GetTime(){return deltaT;}
        float GetRadius(){return radius;}
        float GetMass(){return mass;}

        void SetX(float x){position.x = x;}
        void SetY(float y){position.y = y;}
        void SetZ(float z){position.z = z;}
        void SetPosition(glm::vec3 pos){this->position = pos;}
        void SetVelocity(glm::vec3 v){this->velocity = v;}
        void SetTime(float time){this->deltaT = time;}
        void SetRadius(float radius){this->radius=radius;}
    	float RandomRadius(float alpha, float beta, float dMin, float dMax){
			float b = log10(dMin);	//Linear rescaling factors for desired dMin, dMax range
			float a = log10(dMax) - b;
			//Fill in code for generating k
			//float k = uniform random on (0,1)
			float betaScore = (a + b - 1 - (log10(1/k))/3)/a;	//Corresponding score of beta dist
			int ifault;	//For xinbeta() error flag, currently being ignored
			float betaValue = xinbeta(beta, alpha, log(betaScore), betaScore, &ifault);	//Inverting beta dist
			return pow(10,betaValue);	//Undo log scale
		}


    protected:

    private:
    float deltaT = 0.0001f;
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(0.f,-0.0000001f,0.f);
    float mass;
    float radius;
};

#endif // SPHERE_H
