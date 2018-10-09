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


        float GetX(){return position.x;}
        float GetY(){return position.y;}
        float GetZ(){return position.z;}
        glm::vec3 GetPosition(){return position;}
        glm::vec3 GetVelocity(){return velocity;}
        float GetVelocityX(){return velocity.x;}
        float GetVelocityZ(){return velocity.z;}
        float GetVelocityY(){return velocity.y;}
        float GetTime(){return time;}
        float GetRadius(){return radius;}
        float GetMass(){return mass;}
        //physics getters
        float GetH0(){return h0;}
        float GetRho(){return rho;}
        float GetTau(){return tau;}
        float GetHMax(){return hmax;}
        float GetHStop(){return hstop;}
        bool GetState(){return freefall;}
        float GetTLast(){return tLast;}
        float GetVMax(){return vmax;}


        void SetX(float x){position.x = x;}
        void SetY(float y){position.y = y;}
        void SetZ(float z){position.z = z;}
        void SetPosition(glm::vec3 pos){this->position = pos;}
        void SetVelocity(glm::vec3 v){this->velocity = v;}
        void SetVelocityY(float vY){this->velocity.y = vY;}
        void SetTime(float time){this->time = time;}
        void SetRadius(float radius){this->radius=radius;}

        //physics setters
        void SetH0(float v){this->h0=v;}
        void SetHmax(float v){this->hmax=v;}
        void SetState(bool v){this->freefall = v;}
        void SetTLast(float v){this->tLast = v;}
        void SetVMax(float v){this->vmax =v;}

    	float RandomRadius(float alpha, float beta, float dMin, float dMax){
			float b = log10(dMin);	//Linear rescaling factors for desired dMin, dMax range
			float a = log10(dMax) - b;
			//Fill in code for generating k
			float k = (float) rand()/RAND_MAX;
			float betaScore = (a + b - 1 - (log10(1/k))/3)/a;	//Corresponding score of beta dist
			int ifault;	//For xinbeta() error flag, currently being ignored
			float betaValue = xinbta(beta, alpha, log(betaScore), betaScore, ifault);	//Inverting beta dist
			return pow(10,betaValue);	//Undo log scale
		}


    protected:

    private:
    float time = 0.f;
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(0.f,0.f,0.f);
    float mass;
    float radius;

    //bounce physics
    float h0;
    float hmax; //max height
    float rho = 0.2f; //restituion coeff
    float tau = 0.01f; //contact time for bounce
    float hstop = 0.05f; //stop when bounce is less than 1 cm
    bool freefall = true;  // state: freefall or in contact
    float tLast; //time we would have launched to get to h0 at t=0
    float vmax;

};

#endif // SPHERE_H
