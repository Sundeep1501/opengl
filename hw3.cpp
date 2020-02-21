///////////////////////////////////
// hw3.cpp
//
// OpenGL program to draw a square.
//
// Sundeep penkay.
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
	void print(){
		cout<<x<<", "<<y<<", "<<z<<endl;
	}
};


Point triangleP(0, 0, 0);
Point starP(0, 0, 0);
Point rombusP(0, 0, 0);
Point crossP(0, 0, 0);

// NOTE: NOT USED Draw Circle
void drawCircle(Point p, float radius, int numVertices){
	float t = 0;
	glBegin(GL_POINTS);
	for(int i=0;i<numVertices;++i){
		glVertex3f(p.x+radius*cos(t), p.y+radius*sin(t), p.z);
		t+=2*PI/numVertices;
	}
	glEnd();
}


// Draw Disk with filled surface from inner radius to width
void drawDisk(Point p, float inRadius, float width){
	int numVertices = 100;
	float t = 0;
	glBegin(GL_TRIANGLE_STRIP);
	
	Point ip1 = Point(p.x+inRadius*cos(t), p.y+inRadius*sin(t), p.z);
	Point op1 = Point(p.x+(inRadius+width)*cos(t), p.y+(inRadius+width)*sin(t), p.z);
	
	for(int i=0;i<numVertices;++i){
		Point ip= Point(p.x+inRadius*cos(t), p.y+inRadius*sin(t), p.z);
		Point op = Point(p.x+(inRadius+width)*cos(t), p.y+(inRadius+width)*sin(t), p.z);		
		glVertex3f(ip.x,ip.y,ip.z);		
		glVertex3f(op.x,op.y,op.z);
		t+=2*PI/numVertices;	
	}
	
	glVertex3f(ip1.x,ip1.y,ip1.z);
	glVertex3f(op1.x,op1.y,op1.z);

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

// Draw equilateral triangle around the center point with given side of triangle
void drawEquiTriangle(){
	float radius = N/1.7320;
	
	float t = 90;
	Point A(radius*cos(t), radius*sin(t), 0);
	t+=2*PI/3;
	Point B(radius*cos(t), radius*sin(t), 0);
	t+=2*PI/3;
	Point C(radius*cos(t), radius*sin(t), 0);
	
	drawTriangle(A, B, C);
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

void drawRombus(){
	Point p1(0, N/2, 0.0);
	Point p2(N/-2, 0, 0.0);
	Point p3(0, N/-2, 0.0);
	Point p4(N/2, 0, 0.0);
	drawRectangle(p1, p2, p3, p4);
}

void drawCross(){
	Point p1(N/-2, N/6, 0.0);
	Point p2(N/2, N/6, 0.0);
	Point p3(N/2, N/-6, 0.0);
	Point p4(N/-2, N/-6, 0.0);
	drawRectangle(p1, p2, p3, p4);

	p1 = Point(N/-6, N/2, 0.0);
	p2 = Point(N/6, N/2, 0.0);
	p3 = Point(N/6, N/-2, 0.0);
	p4 = Point(N/-6, N/-2, 0.0);
	drawRectangle(p1, p2, p3, p4);
}
//Draw 5Point star within given center and pentagon diagonal
void draw5PointStar(){

	float radius = N * 0.52573;
	float t = 180;
	Point A(radius*cos(t), radius*sin(t), 0);
	t+=2*PI/5;
	Point D(radius*cos(t), radius*sin(t), 0);
	t+=2*PI/5;
	Point B(radius*cos(t), radius*sin(t), 0);
	t+=2*PI/5;
	Point E(radius*cos(t), radius*sin(t), 0);
	t+=2*PI/5;
	Point C(radius*cos(t), radius*sin(t), 0);

	Point O(0, 0, 0);
	drawTriangle(A,B,O);
	drawTriangle(A,E,O);
	drawTriangle(D,E,O);
	drawTriangle(D,C,O);
	drawTriangle(B,C,O);
}

// Drawing routine.
void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT);
	Point O(0, 0, 0.0);
	glColor3f(0.4, 0.4, 0.4);
	drawDisk(O, ((7*N)/2), N/3);

	glPushMatrix();
	glTranslatef(triangleP.x, triangleP.y, triangleP.z);
	glColor3f(0.0,0.0,1.0);
	drawEquiTriangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(rombusP.x, rombusP.y, rombusP.z);
	glColor3f(1.0, 1.0, 0.0);
	drawRombus();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(crossP.x, crossP.y, crossP.z);
	glColor3f(1.0, 0.0, 0.0);
	drawCross();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(starP.x, starP.y, starP.z);
	glColor3f(0.0, 1.0, 0.0);
	draw5PointStar();
	glPopMatrix();

	glColor3f(0.6, 0.3, 0.1);
	Point p1(W/2, H/2 + 3 * N /2, 0.0);
	Point p2(W/2 - N/2, H/2 + 3*N/2 - N/2, 0.0);
	Point p3(W/2 + N/2, H/2 + 3*N/2 - N/2, 0.0);
	//drawTriangle(p1, p2, p3);

	p1 = Point(W/2 - N/4, H/2 + 3*N/2 - N/2, 0.0);
	p2 = Point(W/2 + N/4, H/2 + 3*N/2 - N/2, 0.0);
	p3 = Point(W/2 + N/4, H/2 - 3*N/2, 0.0);
	Point p4(W/2 - N/4, H/2 - 3*N/2, 0.0);
	//drawRectangle(p1, p2, p3, p4);
	
	glColor3f(0.0, 0.0, 0.0);	
	glBegin(GL_POINTS);
	glVertex3f(O.x, O.y, O.z);
	glEnd();
	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	triangleP = Point(0, ((7*N)/2) - N/3 - N/2, 0.0);
	starP = Point(((-7*N)/2)+N/3+N/2, 0, 0.0);
	rombusP = Point(0, ((-7*N)/2) + N/3 + N/2, 0.0);
	crossP = Point(((7*N)/2)-N/3-N/2, 0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y){
	x = x - W/2;
	y = y - H/2;
	y = y*-1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		float d = sqrt(pow(x-triangleP.x, 2)+pow(y-triangleP.y, 2));
		if(d <= (N/1.7320)){
			cout<<"Triangle"<<endl;
		}
		d = sqrt(pow(x-starP.x, 2)+pow(y-starP.y, 2));
		if(d <= (N/2)){
			cout<<"Star"<<endl;
		}
		d = sqrt(pow(x-rombusP.x, 2)+pow(y-rombusP.y, 2));
		if(d <= (N/2)){
			cout<<"Rhombus"<<endl;
		}
		d = sqrt(pow(x-crossP.x, 2)+pow(y-crossP.y, 2));
		if(d <= (N/2)){
			cout<<"Cross"<<endl;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		exit(0);

	glutPostRedisplay();
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

	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("hw3.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);

	setup();

	glutMainLoop();
}
