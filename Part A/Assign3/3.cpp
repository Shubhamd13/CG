/*
3. Draw inscribed and Circumscribed circles in the triangle as shown as an example below 
(Use any Circle drawing and Line drawing algorithms)
*/
//#include<windows.h>
#include<iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

float X1,Y1,len,TIMES;
void LineDDA(float x1,float Y1,float x2,float y2)
{
    glBegin(GL_POINTS);
    float dx,dy,steps,xinc,yinc,y=Y1,x=x1;
    dx=x1-x2;
    dy=Y1-y2;
    if(fabs(dx)>fabs(dy)){
        steps=(fabs(dx)*10.0f);
    }else{
        steps=(fabs(dy)*10.0f);
    }
    xinc=(float)dx/(float)steps;
    yinc=(float)dy/(float)steps;
    for(float v=0.0;v<=steps;v+=1.0)
    {
		glVertex2f(x,y);
        x-=xinc;
        y-=yinc;
    }
    glEnd();

}
void drawCircle(float xc, float yc, float x, float y)
{
    glVertex2f(xc+x, yc+y);
    glVertex2f(xc-x, yc+y);
    glVertex2f(xc+x, yc-y);
    glVertex2f(xc-x, yc-y);
    glVertex2f(xc+y, yc+x);
    glVertex2f(xc-y, yc+x);
    glVertex2f(xc+y, yc-x);
    glVertex2f(xc-y, yc-x);
}

// Function for circle-generation
// using Bresenham's algorithm
void circleBres(float xc, float yc, float r)
{
    float x = 0, y = r;
    float d = 3 - 2 * r;
	glBegin(GL_POINTS);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
        drawCircle(xc, yc, x, y);
        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
    }
	glEnd();
}

void Draw()
{
int r=1000;
float x=sqrt(pow(r,2)-pow((r/2),2));
 	glClear(GL_COLOR_BUFFER_BIT);
 	glPointSize(3.0);
 	glColor3f(1.0,0.0,0.0);

   	circleBres(0, 0, r);
	circleBres(0, 0, r/2);
	LineDDA(-x,(-r/2),x,(-r/2));
	LineDDA(-x,(-r/2),0,r);
	LineDDA(0,r,x,(-r/2));
    glFlush();
}
void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1000.0, 1000.0, -1000.0, 1000.0);

}
void reshap(int x,int y)
{
    glViewport(0.0,0.0,x,y);
    glutPostRedisplay();
}
int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Window");
	Initialize();
	glutReshapeFunc(reshap);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
