#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>

class Sphere
{
    public:
        Sphere(float x, float y, float z, float radius);

        virtual ~Sphere();

        float GetX(){return position.x;}
        float GetY(){return position.y;}
        float GetZ(){return position.z;}
        float GetRadius(){return radius;}

        void SetX(float x){position.x = x;}
        void SetY(float y){position.y = y;}
        void SetZ(float z){position.z = z;}
        void SetRadius(float radius){this->radius=radius;}


    protected:

    private:
    glm::vec3 position;
    float radius;
};

#endif // SPHERE_H
