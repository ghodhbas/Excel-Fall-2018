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
private:
    glm::vec3 N;
    float D;
};

#endif // PLANE_H
