#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "sphere.h"
#include "spherecontainer.h"

//full header files with functionality
#include "camera.h"

//spheres container
SphereContainer* arr = new SphereContainer();

float frame = 0.f;


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void drawSphere(Sphere* sphere, int frame) {

	glColor4f(0.7f,0.3f,0.1f,0.1f);

    //check if the sphere reached the ground
    if(sphere->GetY() != sphere->GetRadius()){

        if(sphere->GetY()- sphere->GetRadius() >= 0)
        {
            sphere->SetY(sphere->GetY()-0.1f);
        }else{
            sphere->SetY(sphere->GetRadius());
        }
    }

	glTranslatef(sphere->GetX() ,sphere->GetY(),sphere->GetZ());
	glutSolidSphere(sphere->GetRadius(),20,20);

}

void renderScene(void) {

	if (deltaMove || deltaMoveV)
		computePos(deltaMove, deltaMoveV);

	// Clear Color and Depth Buffers
	glClearColor(0.f,0.15f,0.3f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, y, z,
			x+lx, y,  z+lz,
			0.0f, 1.0f,  0.0f);

// Draw ground

	 //grid
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



    if( rand() % 100 <= 10)
    {
        arr->addSphere(Sphere(RandomFloat(-25.f,25.f),50.000f,RandomFloat(-25.f,25.f), 1.00f));
    }


    //draw sphere
    for(int i=0; i<arr->GetSize(); i++)
    {
        glPushMatrix();
        drawSphere(arr->GetSphere(i), frame);
        glPopMatrix();
    }

    if(arr->GetSize()>0)
    {
    std::cout << arr->GetSize() << std::endl;
    }

    glutSwapBuffers();
}
