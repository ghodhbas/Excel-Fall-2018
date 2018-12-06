#ifndef SURFACE_ANALYZER_H
#define SURFACE_ANALYZER_H
#include "sphere.h"
#include <stdlib.h>
#include <iostream>

class Surface_Analyzer
{
    public:
        class SP{
            public:
            int ind;
            float height;
            SP(int i,float h){
                ind = i;
                height = h;
            }
        };

        static bool comp(SP s1, SP s2){
            if(s1.height<s2.height){
                return true;
            }else{
                return false;
            }
        }

        void output_surfacePoints(std::vector<Sphere>& SurfacePoints);

        float roundPoint(float p){
            return roundf(p * 100) / 100;
        }


        Surface_Analyzer();
        virtual ~Surface_Analyzer();


        float x0,z0;
        void GetSurfacePoints(std::vector<Sphere>& SphereContainer, std::vector<Sphere>& SurfacePoints);


    protected:

    private:
};

#endif // SURFACE_ANALYZER_H
