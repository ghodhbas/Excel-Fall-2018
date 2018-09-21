#ifndef SPHERECONTAINER_H
#define SPHERECONTAINER_H

#include <vector>
#include "sphere.h"

class SphereContainer
{
    public:
        SphereContainer();
        virtual ~SphereContainer();

        void addSphere(Sphere sphere);
        Sphere* GetSphere(int position){return &arr->at(position);}
        int GetSize(){return arr->size();}

    protected:

    private:
    std::vector<Sphere>* arr = new std::vector<Sphere>[100];
};

#endif // SPHERECONTAINER_H
