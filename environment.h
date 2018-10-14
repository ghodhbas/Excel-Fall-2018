#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"
#include "physics.h"
#include "plane.h"
#include <math.h>
#include <vector>

//full header files with functionality
#include "camera.h"

int frame=0,timebase,currenttime;

//spheres container
std::vector<Sphere> SphereContainer;

//Physics handler
Physics physics(9.81f);

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


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void drawSphere(Sphere& sphere) {
	glColor4f(0.6f,0.3f,0.1f,1.f);
    //draw in correct postions
	glTranslatef(sphere.GetX() ,sphere.GetY(),sphere.GetZ());
	glutSolidSphere(sphere.GetRadius(),20,20);

}

void animateSphere(Sphere& sphere, int i)
{
    //handle sphere gravity and plane collition
    physics.ApplyGravity(sphere);

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

//    if(sphere.GetY()< sphere.GetRadius())
//        sphere.SetY(sphere.GetRadius());


}

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

// Draw ground
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

    //create ball
    if( rand() % 20 <= 1)
    {
        //randomize position
        glm::vec3 pos(RandomFloat(-17.924f,17.924f),50.f,RandomFloat(-36.f,36.f));
        //create sphere
        float mass = RandomFloat(1.f,3.f);
        float r = mass;
        SphereContainer.push_back(Sphere(pos,mass,r));
    }

    //draw sphere
    for(unsigned int i=0; i<SphereContainer.size(); i++)
    {
        glPushMatrix();
        drawSphere(SphereContainer[i]);
        animateSphere(SphereContainer[i],i);
        glPopMatrix();
    }

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


    //calculate the frames per second
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

    glutSwapBuffers();
}
