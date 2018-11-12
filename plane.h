#ifndef PLANE_H
#define PLANE_H
#include <glm/glm.hpp>

class Plane
{
public:
    Plane(glm::vec3 N, float D);
    virtual ~Plane();
    Plane Normalized();\
    glm::vec3 GetNormal(){return N;}
    float GetD(){return D;}
    float Getx(){return N.x;}
    float Gety(){return N.y;}
    float Getz(){return N.z;}

private:
    glm::vec3 N;
    float D;
};

#endif // PLANE_H
