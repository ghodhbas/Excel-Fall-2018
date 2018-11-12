#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
//full header file with functionality
#include "environment.h"

#define WIDTH 1400
#define HEIGHT 1000

int main(int argc, char **argv) {
    getConePoints();
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(250,100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("APPLICATION");
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
	return 1;
}
