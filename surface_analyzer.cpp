#include "surface_analyzer.h"
#include <math.h>
#include <algorithm>

Surface_Analyzer::Surface_Analyzer(float ratioOfAnalysis, std::vector<Sphere>& SphereContainer, float in)
{
    //calculate min x , max x, min z, max z
    xMax = SphereContainer[0].GetX();
    xMin = SphereContainer[0].GetX();
    zMax = SphereContainer[0].GetZ();
    zMin = SphereContainer[0].GetZ();
    for(int i =1; i< SphereContainer.size();i++){
        if( SphereContainer[i].GetX()> xMax) xMax = SphereContainer[i].GetX();
        if( SphereContainer[i].GetX()< xMin) xMin = SphereContainer[i].GetX();
        if( SphereContainer[i].GetZ()> zMax) zMax = SphereContainer[i].GetZ();
        if( SphereContainer[i].GetZ()< zMin) zMin = SphereContainer[i].GetZ();
    }

    std::cout<<"xMin before ratio: "<<xMin<<std::endl;
    std::cout<<"xMax before ratio: "<<xMax<<std::endl;
    std::cout<<"zMin before ratio:: "<<zMin<<std::endl;
    std::cout<<"zMax before ratio: "<<zMax<<std::endl;
    std::cout<<std::endl;
    //use ratio to decide where to start and end
    xMin = - ((xMax-xMin)*ratioOfAnalysis)/2;
    xMax = -xMin;
    zMin = - ((zMax-zMin)*ratioOfAnalysis)/2;
    zMax = -zMin;
    //save increment?
    incr = in;

    std::cout<<"xMin: "<<xMin<<std::endl;
    std::cout<<"xMax: "<<xMax<<std::endl;
    std::cout<<"zMin: "<<zMin<<std::endl;
    std::cout<<"zMax: "<<zMax<<std::endl;
    std::cout<<"incr: "<<incr<<std::endl;
}

Surface_Analyzer::~Surface_Analyzer()
{
    //dtor
}


void Surface_Analyzer::GetSurfacePoints(std::vector<Sphere>& SphereContainer, std::vector<Sphere>& SurfacePoints){
    x0= xMin;
    z0 = zMin;
    //intital x0 is less then upper bound
    while(x0<xMax){
        //intital z0 is less than upper bound
        while(z0<zMax){
            //container for temporary relevent spheres
            std::vector<SP> temp;
            //iterate through the spheres
            for(int indx =0; indx<SphereContainer.size();indx++){
                //check if sphere position is within range
                float valid  =  pow(SphereContainer[indx].GetX() - x0,2) + pow(SphereContainer[indx].GetZ() - z0,2);
                if(valid < pow(SphereContainer[indx].GetRadius(),2)){
                    float y = pow(SphereContainer[indx].GetRadius(),2) - pow(x0-SphereContainer[indx].GetX(),2) - pow(z0-SphereContainer[indx].GetZ(),2);
                    y = pow(y,0.5f);
                    y= y+ SphereContainer[indx].GetY();
                    temp.push_back(SP(indx,y));
                }
            }

            //If there are any relevent spheres
            if(temp.size()>0){
                //sort array of these relevent spheres
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
            //increment z
            z0 = z0+ incr;
        }
        // increment x and reset z
        x0 = x0 + incr;
        z0 = zMin;
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
