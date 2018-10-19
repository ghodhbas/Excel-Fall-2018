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

/*************************************************************************** PARAMETERS **************************************************************/
//fame - time management
int frame=0,timebase,currenttime;
//spheres container
std::vector<Sphere> SphereContainer;
//Physics handler
Physics physics(9.81f);

/* Cone Creation*/
//rightplane
glm::vec3 N(-0.5f,0.8f,0.f);
Plane rightPlane(N,9.5f);
Plane rp = rightPlane.Normalized();
//leftplane
glm::vec3 N2(0.5f,0.8f,0.f);
Plane leftPlane(N2,9.5f);
Plane lp = leftPlane.Normalized();
//leftplane
glm::vec3 N3(0.f,0.8f,-0.5f);
Plane backPlane(N3,19.f);
Plane bp = backPlane.Normalized();
//leftplane
glm::vec3 N4(0.f,0.8f,0.5f);
Plane frontPlane(N4,19.f);
Plane fp = frontPlane.Normalized();

/*************************************************************************** GENERATION METHODS **************************************************************/

/*Random Float Generator*/
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

/*Generate Randomn Radius based on beta Distrib*/
float RandomRadius(float alpha, float beta, float dMin, float dMax){
    float b = log10(dMin);	//Linear rescaling factors for desired dMin, dMax range
    float a = log10(dMax) - b;
    //Fill in code for generating k
    float k = (float) rand()/RAND_MAX;
    float betaScore = (a + b - 1 - (log10(1/k))/3)/a;	//Corresponding score of beta dist
    int ifault;	//For xinbeta() error flag, currently being ignored
    float betaValue = xinbta(beta, alpha, log(betaScore), betaScore, ifault);	//Inverting beta dist
    return pow(10,betaValue);	//Undo log scale
}

/*Randomly creates a Sphere and add it to the container*/
void createSphere()
{
    if( rand() % 10 <= 1)
    {
        //randomize position
        glm::vec3 pos(RandomFloat(-17.924f,17.924f),100.f,RandomFloat(-36.f,36.f));
        //create sphere
        float mass = RandomFloat(0.2f,0.8f);
        //mass vol 2.4 gram per cubic cm
        float r = mass*5.f;
        SphereContainer.push_back(Sphere(pos,mass,r));
    }
}

/*************************************************************************** MISC METHODS **************************************************************/

void drawGrid()
{
    glColor3f(0.f,0.f,0.f);
    GLfloat fExtent = 50.0f;
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

void DrawCone()
{
    //draw side
    glBegin(GL_QUADS);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(50.f,20.047f,-68.752f);
    glVertex3f(17.924f,0.f,-36.f);
    glVertex3f(17.924f,0.f,36.f);
    glVertex3f(50.f,20.047f,68.752f);
    glEnd();
    //draw left side
    glBegin(GL_QUADS);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(-50.f,20.047f,-68.752f);
    glVertex3f(-17.924f,0.f,-36.f);
    glVertex3f(-17.924f,0.f,36.f);
    glVertex3f(-50.f,20.047f,68.752f);
    glEnd();
    //draw left side
    glBegin(GL_QUADS);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(-50.f,20.5f,68.752f);
    glVertex3f(50.f,20.5f, 68.752f);
    glVertex3f(17.924f,0.f,36.f);
    glVertex3f(-17.924f,0.f,36.f);
    glEnd();
    //draw front side
    glBegin(GL_QUADS);
    glColor4f(0.f,0.7f,0.5f,0.5f);
    glVertex3f(-50.f,20.5f,-68.752f);
    glVertex3f(50.f,20.5f, -68.752f);
    glVertex3f(17.924f,0.f,-36.f);
    glVertex3f(-17.924f,0.f,-36.f);
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
      for(int j=i+1;j<SphereContainer.size(); j++)
    {
        if(sphere.DetectCollision(SphereContainer[j])){
            sphere.CollisionResponse(SphereContainer[j]);
        }
    }
    //side collisions
    if(sphere.DetectCollision(rp))
        sphere.CollisionResponse(rp);
    if(sphere.DetectCollision(lp))
        sphere.CollisionResponse(lp);
    if(sphere.DetectCollision(bp))
        sphere.CollisionResponse(bp);
    if(sphere.DetectCollision(fp))
        sphere.CollisionResponse(fp);
    //handle sphere gravity and plane collition
    physics.ApplyGravity(sphere);
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
	glutSolidSphere(sphere.GetRadius(),8,8);

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
    // Draw Grid
    drawGrid();
    //create ball
    std::thread crs(createSphere);
    //apply physics
    std::thread spherePhysics(animate);
    //render Spheres
    render();
    //render cone
    DrawCone();
    //calculate the frames per second
    displayFPS();
    //join threads
    spherePhysics.join();
    crs.join();
    //swap buffers
    glutSwapBuffers();
}















