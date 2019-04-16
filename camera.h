
// angle of rotation for the camera direction
float angle = 0.0f;
float cameraSpeed = 3.f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, y=5.0f, z=70.0f;

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


void computePos(float deltaMove, float deltaMoveV) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
	y += deltaMoveV * 0.1f;
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





