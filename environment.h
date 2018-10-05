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

//plane
glm::vec3 N(-0.5f,0.8f,0.f);
Plane rightPlane(N,9.5f);
Plane p1 = rightPlane.Normalized();


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void drawSphere(Sphere& sphere) {
	glColor4f(0.6f,0.3f,0.1f,1.f);
    //handle sphere gravity and plane collition
    physics.ApplyGravity(sphere);
    //side collision
     if(sphere.DetectCollision(p1))
    {   //collision distance
        float distanceCenterFromPlane = fabs(glm::dot(p1.GetNormal(), sphere.GetPosition()) + p1.GetD());
        float distanceFromPlane = fabs(distanceCenterFromPlane - sphere.GetRadius());
        //update position speed and energy lost
        sphere.SetPosition(sphere.GetPosition()+ p1.GetNormal() * distanceFromPlane);
        sphere.SetTime(sphere.GetTime()+sphere.GetTau());
        sphere.SetVMax(sphere.GetVMax() * sphere.GetRho());
        sphere.SetVelocity(glm::reflect(sphere.GetVelocity(),p1.GetNormal()) *sphere.GetRho());
    }


    //draw in correct postions
	glTranslatef(sphere.GetX() ,sphere.GetY(),sphere.GetZ());
	glutSolidSphere(sphere.GetRadius(),20,20);

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
			x+lx, y,  z+lz,
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
    if( rand() % 180 <= 1)
    {
        //randomize position
        glm::vec3 pos(RandomFloat(-30.f,30.f),50.f,RandomFloat(-20.f,20.f));
        //create sphere
        SphereContainer.push_back(Sphere(pos,10.f,1.f));
    }

    //draw sphere
    for(unsigned int i=0; i<SphereContainer.size(); i++)
    {
        glPushMatrix();
        drawSphere(SphereContainer[i]);
        glPopMatrix();
    }

    //draw side

    glBegin(GL_QUADS);
    glColor4f(0.f,0.7f,0.5f,0.4f);
    glVertex3f(50.f,20.047f,-30.f);
    glVertex3f(17.924f,0.f,-30.f);
    glVertex3f(17.924f,0.f,30.f);
    glVertex3f(50.f,20.047f, 30.f);
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
