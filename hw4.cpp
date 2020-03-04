#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#define MSEC_PER_FRAME 33
int isPaused = 1;

// class to hold 3D point
class Point{
	public:
		float x,y,z;
	Point(float a, float b, float c){
		x = a;
		y = b;
		z = c;
	}
};

//Draw Rectangle
void drawRectangle(Point p1, Point p2, Point p3, Point p4){
	glBegin(GL_POLYGON);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

void drawRombus(){
	Point p1(-8.0, -5, -1.0);
	Point p2(8.0, -5, -1.0);
	Point p3(8.0, -5, -1001.0);
	Point p4(-8.0, -5, -1001.0);

	glColor3f(0.3, 0.3, 0.3);
	drawRectangle(p1, p2, p3, p4);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the buffers including the depth buffer.

	// draw Road
	drawRombus();
	
	// draw road borders
	glColor3f(0.0,0,0);
	glBegin(GL_LINES);
		glVertex3f(8,-5,-1); //Starts from bottom-right corner
		glVertex3f(8,-5,-1001); //goes until the far plane
	
		glVertex3f(-8,-5,-1); //Starts from bottom-left corner
		glVertex3f(-8,-5,-1001);//goes until the far plane
	glEnd();

	// draw divider
	glColor3f(1, 1, 1);
	Point p1(-1.0, -5, -1.0);
	Point p2(1.0, -5, -1.0);
	Point p3(1.0, -5, -6.0);
	Point p4(-1.0, -5, -6.0);
	for(int i=0;i<200;i++){
		drawRectangle(p1, p2, p3, p4);
		p1.z-=10;
		p2.z-=10;
		p3.z-=10;
		p4.z-=10;
	}
	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glFrustum(-8.0, 8.0, -5.0, 5.0, 1.0, 1001.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

float eyeZ = 0.0;
void moveForward(int value){
	eyeZ+=1.0;
	//gluLookAt(0.0, 4.0, eyeZ, 0, 0, eyeZ+5, 0, 1.0, 0.0);
	//First 3 params are the center of camera eye
	//Second 3 params are direction of camera
	//Last 3 params are upside (up direction) of camera
	//glutTimerFunc(MSEC_PER_FRAME, moveForward, 1);
	glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
	switch (key){
		case 27:
			exit(0);
			break;
		case 32:
			glutTimerFunc(MSEC_PER_FRAME, moveForward, 1);
			break;
		default:
			break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Perspective Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	//glewExperimental = GL_TRUE;
	//glewInit();

	setup();

	glutMainLoop();
}
