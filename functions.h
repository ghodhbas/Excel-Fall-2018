#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "sphere.h"
#include "spherecontainer.h"

//spheres container
SphereContainer* arr = new SphereContainer();

float frame = 0.f;

// angle of rotation for the camera direction
float angle = 0.0f;
float cameraSpeed = 3.f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, y=10.0f, z=50.0f;

// the key states. These variables will be zero
//when no key is being presses
float mouseSensibility = 0.005f;
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
float deltaMove = 0;
float deltaMoveV = 0;
int xOrigin = -1;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

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

void computePos(float deltaMove, float deltaMoveV) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
	y += deltaMoveV * 0.1f;
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

void processNormalKeys(unsigned char key, int xx, int yy) {

        switch ( key ) {
            case 27: /* Escape key */
                exit ( 0 );
                break;

        }
}

void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = cameraSpeed; break;
             case GLUT_KEY_DOWN : deltaMove = -cameraSpeed; break;
             case GLUT_KEY_LEFT : deltaMoveV = -cameraSpeed;break;
             case GLUT_KEY_RIGHT : deltaMoveV = +cameraSpeed;break;

       }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
             case GLUT_KEY_LEFT :
             case GLUT_KEY_RIGHT : deltaMoveV = 0;break;
        }
}

void mouseMove(int x, int y) {

         // this will only be true when the left button is down
         if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngleX = (x - xOrigin) * mouseSensibility;

		// update camera's direction
		lx = sin(angle + deltaAngleX);
		lz = -cos(angle + deltaAngleX);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngleX;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}





