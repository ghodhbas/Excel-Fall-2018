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


void Surface_Analyzer::GetSurfacePoints(std::vector<Sphere>& SphereContainer, std::vector<Sphere>& SurfacePoints){
    while(x0<25){
        while(z0<25){
            std::vector<SP> temp;
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
                //sort array
                std::sort(temp.begin(),temp.end(),comp);
                //get highest sphere
                Sphere s = SphereContainer[temp[temp.size()-1].ind];
                //update height from intersection point
                s.SetY(temp[temp.size()-1].height);
                //check for duplicates not using binary search because run time is not a problem
                bool duplicate = false;
                for(unsigned int j =0;j<SurfacePoints.size();j++){
                    float x1 = s.GetX();
                    float x2 = SurfacePoints[j].GetX();
                    float z1 = s.GetZ();
                    float z2 = SurfacePoints[j].GetZ();

                    if( fabs(x1-x2)<0.001f && fabs(z1-z2) < 0.001f){
                        float y1 = s.GetY();
                        float y2 = SurfacePoints[j].GetY();
                        if(y1> y2){
                            //update duplicate
                            SurfacePoints[j]=s;
                        }
                        duplicate = true;
                        break;
                    }
                }
                //insert if there are no duplicates
                if(!duplicate) SurfacePoints.push_back(s);
            }
            z0 = z0+ 1.f;
        }
        x0 = x0+ 1.f;
        z0 = -25.f;
    }
}

void Surface_Analyzer::output_surfacePoints(std::vector<Sphere>& SurfacePoints){
    //open output file
    std::sort(SurfacePoints.begin(),SurfacePoints.end(),Sphere::comp);
    FILE *out = fopen("Output-sorted.csv", "w");
    if (out == NULL)
    {
        printf("Error opening output file!\n");
        exit(1);
    }

    //print outpuy
    for(int i = 0;i< SurfacePoints.size();i++){
        fprintf(out,"%3.2f, %3.2f, %3.2f, %3.2f \n",roundPoint(SurfacePoints[i].GetX()),roundPoint(SurfacePoints[i].GetY()),roundPoint(SurfacePoints[i].GetZ()),roundPoint(SurfacePoints[i].GetRadius()));
    }
    //close output
    fclose(out);
    printf("Output generated\n");

}
