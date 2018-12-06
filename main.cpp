#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
//full header file with functionality
#include "environment.h"
#include <algorithm>
#include "surface_analyzer.h"

#define WIDTH 1400
#define HEIGHT 1000

float Sphere::rho = 0.3f;
float Sphere::pE = 0.8f;



int main(int argc, char **argv) {
    //directory
    std::cout << argv[0] << std::endl;
    //with input
    if(argc >1){
        //height of cone
        float height = atof(argv[1]);
        //coefficient of angle of come
        c=atof(argv[2]);
        createCone(c);
        //gravity and Drag value
        physics = Physics(atof(argv[3]),atof(argv[4]));
        //Drop Height
        dropHeight=atof(argv[5]);
        //eleasticity
        Sphere::rho = atof(argv[6]);
        Sphere::pE = atof(argv[7]);
        //number of disks
        maxSphereCount = atof(argv[8]);
        //max time steps
        maxTimeStep = atof(argv[9]);
        showSimul=atof(argv[10]);
        getConePoints(height);
    }else{
        //height of cone
        float height = 100.f;
        //coefficient of angle of come
        c=1.2f;
        createCone(c);
        //Drag value
        physics = Physics(9.81f,0.99f);
        //Drop Height
        dropHeight=200.f;
        //gravity
        //eleasticity
        Sphere::rho = 0.1f;
        Sphere::pE = 0.7f;
        //number of disks
        maxSphereCount = 1000;
        //max time steps
        maxTimeStep = 5000;
        showSimul=false;
        getConePoints(height);
    }

    std::cout<<"gravity : "<<physics.GetGravity()<<std::endl;
    std::cout<<"Drag : "<<physics.GetDrag()<<std::endl;
    std::cout<<"Drop Height : "<<dropHeight<<std::endl;
    std::cout<<"Rho/elas: "<<Sphere::rho<<"/"<<Sphere::pE<<std::endl;
    std::cout<<"Max Sphere Number: "<<maxSphereCount<<std::endl;
    std::cout<<"Max Time Steps before exiting: "<<maxTimeStep<<std::endl;



    if(showSimul){
        glutInit(&argc, argv);
        // init GLUT and create window
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(250,100);
        glutInitWindowSize(WIDTH, HEIGHT);
        glutCreateWindow("3D Simulation");
        glEnable(GL_DEPTH_TEST);
        //display
        glEnable(GL_BLEND);// you enable blending function
        // Light Settings
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        GLfloat lightpos[] = {.5, 4., 1., 0.};
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
        glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
        glEnable ( GL_COLOR_MATERIAL ) ;
        GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
        //rendering callbacks
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);
        //keyboard inputs management
        glutIgnoreKeyRepeat(0);
        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(pressKey);
        glutSpecialUpFunc(releaseKey);
        //Mouse inputs management
        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);
        // enter GLUT event processing cycle
        glutMainLoop();
    }else{
        int i=0;
        //add extra time for system to settle
        while(i<maxTimeStep){
            renderScene();
            i++;
        }
    }

    std::cout<<SphereContainer.size()<<std::endl;

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Data Generation Complete, Starting Sorting and Surface points generation: "<<std::endl;
    std::sort(SphereContainer.begin(),SphereContainer.end(), Sphere::comp);
    std::cout<<"Data Sorted... "<<std::endl;

    Surface_Analyzer* SA = new Surface_Analyzer();
    std::vector<Sphere> SurfacePoints;
    SA->GetSurfacePoints(SphereContainer, SurfacePoints);
    SA->output_surfacePoints(SurfacePoints);

	return 1;
}



