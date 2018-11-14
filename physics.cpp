#include "physics.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

/*****************Constructor***********************************/
Physics::Physics(float gravity, float drag)
{
   this->gravity = gravity;
   this->drag = drag;
}
Physics::~Physics()
{
}

/*****************Accelerate Spheres***********************************/

void Physics::ApplyGravity(Sphere& sphere, Plane& rp,Plane& lp,Plane& bp,Plane& fp){
        //calculate new position
    //if( glm::length(sphere.GetVelocity()) > 0.1f || sphere.GetY()>100.f){
        if(!(sphere.DetectCollision(rp) || sphere.DetectCollision(fp) || sphere.DetectCollision(lp) || sphere.DetectCollision(bp))){
            float newVelocityY = sphere.GetVelocityY()- gravity * dt *dt;
            sphere.SetVelocityY(newVelocityY);
            float hnew = sphere.GetY() + sphere.GetVelocityY() * dt;
            float xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
            float znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
            glm::vec3 pos(xnew,hnew,znew);
            sphere.SetPosition(pos);
        }
        //apply drag
        if(sphere.GetY()<90.f) sphere.SetVelocity(sphere.GetVelocity()*GetDrag());
    //}
        sphere.SetPosition(sphere.GetPosition());
//
//    if(glm::length(sphere.GetVelocity())<1.f && sphere.DetectCollision(rp)){
//        sphere.SetVelocity(-lp.GetNormal() * 0.5f);
//        float hnew = sphere.GetY() + sphere.GetVelocityY() * dt;
//        float xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
//        float znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
//        glm::vec3 pos(xnew,hnew,znew);
//        sphere.SetPosition(pos);
//
//    }
//    if(glm::length(sphere.GetVelocity())<1.f && sphere.DetectCollision(lp) && sphere.GetY()>10.f){
//        sphere.SetVelocity(-rp.GetNormal() * 0.5f);
//        float hnew = sphere.GetY() + sphere.GetVelocityY() * dt;
//        float xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
//        float znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
//        glm::vec3 pos(xnew,hnew,znew);
//        sphere.SetPosition(pos);
//    }
//    if(glm::length(sphere.GetVelocity())<1.f && sphere.DetectCollision(bp) && sphere.GetY()>10.f){
//        sphere.SetVelocity(-fp.GetNormal()* 0.5f);
//        float hnew = sphere.GetY() + sphere.GetVelocityY() * dt;
//        float xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
//        float znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
//        glm::vec3 pos(xnew,hnew,znew);
//        sphere.SetPosition(pos);
//    }
//    if(glm::length(sphere.GetVelocity())<0.5f && sphere.DetectCollision(fp) && sphere.GetY()>10.f){
//        sphere.SetVelocity(-bp.GetNormal() * 0.5f );
//        float hnew = sphere.GetY() + sphere.GetVelocityY() * dt;
//        float xnew = sphere.GetX() + sphere.GetVelocityX() * dt;
//        float znew = sphere.GetZ() + sphere.GetVelocityZ() * dt;
//        glm::vec3 pos(xnew,hnew,znew);
//        sphere.SetPosition(pos);
//    }
}

