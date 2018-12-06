#include "surface_analyzer.h"
#include <math.h>
#include <algorithm>
Surface_Analyzer::Surface_Analyzer()
{
    z0 = -25.f;
    x0 = -25.f;
}

Surface_Analyzer::~Surface_Analyzer()
{
    //dtor
}


void Surface_Analyzer::GetSurfacePoints(std::vector<Sphere>& SphereContainer){
    //start from x0/z0 and do duble for loo and get relevent spheres
    std::cout<<"number of spheres: "<<SphereContainer.size()<<std::endl;

    int iter = 0;
    while(x0<25){
        while(z0<25){
            std::vector<SP> temp;
            //std::cout<<"X0 "<< x0<<std::endl;
            //std::cout<<"z0 "<< z0<<std::endl;
            for(int indx =0; indx<SphereContainer.size();indx++){
                float valid  =  pow(SphereContainer[indx].GetX() - x0,2) + pow(SphereContainer[indx].GetZ() - z0,2);
                if(valid < pow(SphereContainer[indx].GetRadius(),2)){
                    float y = pow(SphereContainer[indx].GetRadius(),2) - pow(x0-SphereContainer[indx].GetX(),2) - pow(z0-SphereContainer[indx].GetZ(),2);
                    y = pow(y,0.5f);
                    y= y+ SphereContainer[indx].GetY();

                    temp.push_back(SP(indx,y));
                }
            }
            if(temp.size()>0){
                std::sort(temp.begin(),temp.end(),Surface_Analyzer::comp);
                std::cout<<"Size of temp array is "<<temp.size()<<std::endl;
                std::cout<<"Sphere with heighest height in iteration "<<iter<<" has height "<<temp[temp.size()-1].height << " and index "<<temp[temp.size()-1].ind<<std::endl;
                std::cout<<"X: "<< SphereContainer[temp[temp.size()-1].ind].GetX()<<std::endl;
                std::cout<<"Z: "<< SphereContainer[temp[temp.size()-1].ind].GetZ()<<std::endl;
                std::cout<<"Y: "<< SphereContainer[temp[temp.size()-1].ind].GetY()<<std::endl;
                std::cout<<std::endl;
            }
            z0 = z0+ 1.f;
            iter++;
        }
        x0 = x0+ 1.f;
        z0 = -25.f;
    }
}
