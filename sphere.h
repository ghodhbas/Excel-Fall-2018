#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>

class Sphere
{
    public:
        Sphere(float x, float y, float z, float mass, float radius);

        virtual ~Sphere();

        float GetX(){return position.x;}
        float GetY(){return position.y;}
        float GetZ(){return position.z;}
        glm::vec3 GetPosition(){return position;}
        glm::vec3 GetVelocity(){return velocity;}
        float GetTime(){return deltaT;}
        float GetRadius(){return radius;}

        void SetX(float x){position.x = x;}
        void SetY(float y){position.y = y;}
        void SetZ(float z){position.z = z;}
        void SetPosition(glm::vec3 pos){this->position = pos;}
        void SetVelocity(glm::vec3 v){this->velocity = v;}
        void SetTime(float time){this->deltaT = time;}
        void SetRadius(float radius){this->radius=radius;}


    protected:

    private:
    float deltaT = 0.1f;
    glm::vec3 position;
    glm::vec3 velocity;
    float mass;
    float radius;
};

#endif // SPHERE_H
