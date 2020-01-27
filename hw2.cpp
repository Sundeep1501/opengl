///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
using namespace std;
#define PI 3.14159265358979324
#define N 50.0
#define W 500.0
#define H 500.0

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

// Draw Circle
void drawCircle(Point p, float radius, int numVertices){
	float t = 0;
	glBegin(GL_POLYGON);
	for(int i=0;i<numVertices;++i){
		glVertex3f(p.x+radius*cos(t), p.y+radius*sin(t), p.z);
		t+=2*PI/numVertices;
	}
	glEnd();
}


// Draw Triangle
void drawTriangle(Point p1, Point p2, Point p3){
	glBegin(GL_TRIANGLES);
	glVertex3f(p1.x,p1.y,p1.z);
	glVertex3f(p2.x,p2.y,p2.z);
	glVertex3f(p3.x,p3.y,p3.z);
	glEnd();
}

//Draw Rectangle
void drawRectangle(Point p1, Point p2, Point p3, Point p4){
	glBegin(GL_POLYGON);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

//Draw 5Point star within given center and pentagon diagonal
void draw5PointStar(Point O, float diag){

	float radius = diag * 0.52573;
	float t = 180;
	Point A(O.x+radius*cos(t), O.y+radius*sin(t), O.z);
	t+=2*PI/5;
	Point D(O.x+radius*cos(t), O.y+radius*sin(t), O.z);
	t+=2*PI/5;
	Point B(O.x+radius*cos(t), O.y+radius*sin(t), O.z);
	t+=2*PI/5;
	Point E(O.x+radius*cos(t), O.y+radius*sin(t), O.z);
	t+=2*PI/5;
	Point C(O.x+radius*cos(t), O.y+radius*sin(t), O.z);

	drawTriangle(A,B,O);
	drawTriangle(A,E,O);
	drawTriangle(D,E,O);
	drawTriangle(D,C,O);
	drawTriangle(B,C,O);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Point O(W/2, H/2, 0.0);
	glColor3f(0.4, 0.4, 0.4);
	drawCircle(O, (7*N)/2, 500);
	glColor3f(1.0, 1.0, 1.0);
	drawCircle(O, ((7*N)/2) - (N/3), 500);

	glColor3f(0.0,0.0,1.0);
	Point p1(W/2, H/2 + ((7*N)/2) - N/3, 0.0);
	Point p2(W/2 - N/2, H/2 + ((7*N)/2) - (N/3)-N, 0.0);
	Point p3(W/2 + N/2, H/2 + ((7*N)/2) - (N/3)-N, 0.0);
	drawTriangle(p1, p2, p3);
	
	glColor3f(1.0, 1.0, 0.0);
	p1 = Point(W/2, H/2 - ((7*N)/2) + N/3 + N, 0.0);
	p2 = Point(W/2 - N/2, H/2 - ((7*N)/2) + (N/3)+(N/2),0.0);
	p3 = Point(W/2 + N/2, H/2 - ((7*N)/2) + (N/3)+(N/2),0.0);
	drawTriangle(p1, p2, p3);
	
	p1 = Point(W/2, H/2 - ((7*N)/2) + N/3, 0.0);
	p2 = Point(W/2 - N/2, H/2 - ((7*N)/2) + (N/3)+(N/2), 0.0);
	p3 = Point(W/2 + N/2, H/2 - ((7*N)/2) + (N/3)+(N/2), 0.0);
	drawTriangle(p1, p2, p3);

	glColor3f(1.0, 0.0, 0.0);
	p1 = Point(W/2+((7*N)/2) - N/3 - N, H/2 + N/6, 0.0);
	p2 = Point(W/2+((7*N)/2) - N/3, H/2 + N/6, 0.0);
	p3 = Point(W/2+((7*N)/2) - N/3, H/2 - N/6, 0.0);
	Point p4(W/2+((7*N)/2) - N/3 - N, H/2 - N/6, 0.0);
	drawRectangle(p1, p2, p3, p4);

	p1 = Point(W/2+((7*N)/2)-N/3-N/2-N/6, H/2+N/2, 0.0);
	p2 = Point(W/2+((7*N)/2)-N/3-N/2+N/6, H/2+N/2, 0.0);
	p3 = Point(W/2+((7*N)/2)-N/3-N/2+N/6, H/2-N/2, 0.0);
	p4 = Point(W/2+((7*N)/2)-N/3-N/2-N/6, H/2-N/2, 0.0);
	drawRectangle(p1, p2, p3, p4);

	glColor3f(0.0, 1.0, 0.0);
	p1 = Point(W/2-((7*N)/2)+N/3+N/2, H/2, 0.0);
	draw5PointStar(p1, N);

	glColor3f(0.6, 0.3, 0.1);

	p1 = Point(W/2, H/2 + 3 * N /2, 0.0);
	p2 = Point(W/2 - N/2, H/2 + 3*N/2 - N/2, 0.0);
	p3 = Point(W/2 + N/2, H/2 + 3*N/2 - N/2, 0.0);
	drawTriangle(p1, p2, p3);

	p1 = Point(W/2 - N/4, H/2 + 3*N/2 - N/2, 0.0);
	p2 = Point(W/2 + N/4, H/2 + 3*N/2 - N/2, 0.0);
	p3 = Point(W/2 + N/4, H/2 - 3*N/2, 0.0);
	p4 = Point(W/2 - N/4, H/2 - 3*N/2, 0.0);
	drawRectangle(p1, p2, p3, p4);
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
	glOrtho(0.0, W, 0.0, H, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

//	glutInitContextVersion(4, 3);
//	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("square.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
