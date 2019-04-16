/*This Header file includes functionality of the environment*/
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"
#include "physics.h"
#include "plane.h"
#include <math.h>
#include <vector>
#include <thread>
#include "camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>


/*************************************************************************** PARAMETERS **************************************************************/
//frame - time management
bool showSimul= true;
int frame=0,timebase,currenttime;
unsigned long timeStep =0;
unsigned long maxTimeStep=0;
//spheres container
std::vector<Sphere> SphereContainer;
//radius distribution
InputReader distribution;

//Physics handler
Physics physics(9.81f,0.99f);

int maxSphereCount = 0;
int count=0;
float dropHeight = 20.f;

float c = 0.2f;
glm::vec3 N(-1.f,1.f,0.f);
Plane rp(N,0.f);
Plane fp(N,0.f);;
Plane bp(N,0.f);;
Plane lp(N,0.f);;

/* Cone Creation*/
void createCone(float c){
    //rightplane
    glm::vec3 N(-1.f,1.f*c,0.f);
    Plane rightPlane(N,0.f);
    rp = rightPlane.Normalized();

    //leftplane
    glm::vec3 N2(1.f,1.f*c,0.f);
    Plane leftPlane(N2,0);
    lp = leftPlane.Normalized();

    //back plane
    glm::vec3 N3(0.f,1.f*c,1.f);
    Plane backPlane(N3,0.f);
    bp = backPlane.Normalized();

    //fronntplane
    glm::vec3 N4(0.f,1.f*c,-1.f);
    Plane frontPlane(N4,0.f);
    fp = frontPlane.Normalized();
}

//intersections
float x1 = 0;
float x2,x3,x4,z1,z2,z3,z4,y11,y22,y33,y44;

/*************************************************************************** GENERATION METHODS **************************************************************/
/*Random Float Generator*/
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

/*Generate Randomn Radius piecewise distribution using cdf --- UNIT Millimiter*/
float RandomRadius(){
    int prob = rand() % 100;
    //std::cout<< "value tested: "<<prob<<std::endl;
    int index = distribution.get_low(prob);
    //std::cout<< "lower bound index: "<<index<<std::endl;
    float low_diameter ;
    float high_diameter;
    if (index ==0){
        low_diameter = 0;
        high_diameter = distribution.get_diameter(index);
    }else{
        low_diameter = distribution.get_diameter(index-1);
        high_diameter = distribution.get_diameter(index);
    }
    //std::cout<< "lower diameter: "<<low_diameter<<std::endl;
    //std::cout<< "high diameter:  "<<high_diameter<<std::endl;

    return RandomFloat(low_diameter,high_diameter)/2;

}

/*Randomly creates a Sphere and add it to the container*/
void createSphere()
{   if(count < maxSphereCount+1){
        if( rand() % 10 <= 1)
        {
            //randomize position
            glm::vec3 pos(RandomFloat(-20.f,20.f),dropHeight,RandomFloat(-12.f,12.f));
            //create sphere


            float r = RandomRadius(); // radius is in millimiter
            //conver radius to cm
            r = r/10;
            //calculate volume in cubic cm
            float v = (r*r*r * 3.14 *4 )/3;
            float mass = v* 10.f; //mass vol 2.4 gram per cubic cm
            //std::cout<< "mass: "<<mass/1000.f<<std::endl;
            //std::cout<< "radius: "<<r/100.f<<std::endl;

            SphereContainer.push_back(Sphere(pos, mass, r ));
            count++;
        }
    }
}

/*************************************************************************** MISC METHODS **************************************************************/

void drawGrid()
{
    glColor3f(0.f,0.f,0.f);
    GLfloat fExtent = 30.0f;
	GLfloat fStep = 1.0f;
    GLfloat y = 0.f;
    GLint iLine;
    glBegin(GL_LINES);
    for(iLine = -fExtent; iLine <= fExtent; iLine += fStep)
    {
        glVertex3f(iLine, y, fExtent); // Draw Z lines
        glVertex3f(iLine, y, -fExtent);
        glVertex3f(fExtent, y, iLine);
        glVertex3f(-fExtent, y, iLine);
    }
    glEnd();
}

void getConePoints(float height){
    //intersection between rp and fp at hight 100
    glm::vec3 dir = glm::cross(rp.GetNormal(),fp.GetNormal());
    dir = glm::normalize(dir);
    dir = -dir * height;

    x1=dir.x;
    y11=dir.y;
    z1=dir.z;

    //rp bp intersectiom
    dir = glm::cross(rp.GetNormal(),bp.GetNormal());
    dir = glm::normalize(dir);
    dir = dir * height;

    x2=dir.x;
    y22=dir.y;
    z2=dir.z;

    // lp bp intersectiom
    dir = glm::cross(lp.GetNormal(),bp.GetNormal());
    dir = glm::normalize(dir);
    dir = -dir * height;

    x3=dir.x;
    y33=dir.y;
    z3=dir.z;

    //fp lp intersectiom
    dir = glm::cross(fp.GetNormal(),lp.GetNormal());
    dir = glm::normalize(dir);
    dir = -dir * height;

    x4=dir.x;
    y44=dir.y;
    z4=dir.z;
}

void DrawCone()
{
    //draw right
    glBegin(GL_TRIANGLES);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(x1,y11,z1);
    glVertex3f(x2,y22,z2);
    glEnd();

   //draw left side
    glBegin(GL_TRIANGLES);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(x4,y44,z4);
    glVertex3f(x3,y33,z3);
    glEnd();
    //draw front side
    glBegin(GL_TRIANGLES);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(x4,y44,z4);
    glVertex3f(x1,y11,z1);
    glEnd();
    //draw back side
    glBegin(GL_TRIANGLES);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(x2,y22,z2);
    glVertex3f(x3,y33,z3);
    glEnd();
}

/*Print fps to the console*/
void displayFPS()
{
    frame++;
	//get the current time
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	//check if a second has passed
	if (currenttime - timebase > 1000)
	{
		std::cout <<"FPS: "<< (int) (frame*1000.0/(currenttime-timebase)) << std::endl;
	 	timebase = currenttime;
		frame = 0;
	}
}

/******************************************************Physics handling***************************************************************/
/*Handle Sphere animation and physics of sphere*/
void animateSphere(Sphere& sphere, int i)
{
    //handle sphere gravity and plane collition
    physics.ApplyGravity(sphere,rp,lp,bp,fp);

    //side collisions
    if(sphere.DetectCollision(rp)){
        sphere.CollisionResponse(rp);
    }

    if(sphere.DetectCollision(lp)){
        sphere.CollisionResponse(lp);
    }

    if(sphere.DetectCollision(bp)){
        sphere.CollisionResponse(bp);
    }

    if(sphere.DetectCollision(fp)){
        sphere.CollisionResponse(fp);
    }
    //Sphere Collisions
      for(int j=i+1;j<SphereContainer.size(); j++)
    {
        if(sphere.DetectCollision(SphereContainer[j])){
            sphere.CollisionResponse(SphereContainer[j]);
        }
    }
}

/*apply physics on all spheres in the environment*/
void animate()
{
    for(unsigned int i=0; i<SphereContainer.size(); i++)
    {
        animateSphere(SphereContainer[i],i);
    }

}

/********************************************************************************Rendering**************************************************/
/*Draw Sphere*/
void drawSphere(Sphere& sphere) {
	glColor4f(0.6f,0.3f,0.1f,1.f);
    //draw in correct postions
	glTranslatef(sphere.GetX() ,sphere.GetY(),sphere.GetZ());
	glutSolidSphere(sphere.GetRadius(),10,10);
}
/*Render Spheres*/
void render()
{
     //draw sphere
    for(unsigned int i=0; i<SphereContainer.size(); i++)
    {
        glPushMatrix();
        drawSphere(SphereContainer[i]);
        glPopMatrix();
    }
}

/*Render Environment*/
void renderScene(void) {
    if(showSimul){
        //camera movement
        if (deltaMove || deltaMoveV)
            computePos(deltaMove, deltaMoveV);

        // Clear Color and Depth Buffers
        glClearColor(0.f,0.15f,0.3f,0.7f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();
        // Set the camera
        gluLookAt(	x, y, z,
                    0,0,0,
                0.0f, 1.0f,  0.0f);
    }
    //create ball
    std::thread crs(createSphere);
    //apply physics
    std::thread spherePhysics(animate);
    if(showSimul){
        //std::cout<<"RENDERING"<<std::endl;
        //render Spheres
        render();
        //render cone
        drawGrid();
        DrawCone();
    }
    //calculate the frames per second
    displayFPS();
    //join threads
    spherePhysics.join();
    crs.join();
    if(count%100 == 0) std::cout<<"Count: "<<count<<std::endl;

    timeStep++;
    //std::cout<<"time: "<<timeStep<<std::endl;
    //swap buffers
    if(showSimul){
        glutSwapBuffers();
    }

}















