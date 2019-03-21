/*
4. Draw the following pattern using any Line drawing algorithms.
*/
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
void Draw()
{
    float X1,Y1,len;
    X1=::X1;
    Y1=::Y1;
    len=::len;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0);
    glColor3f(1.0,0.0,0.0);
    for(int i=0;i<TIMES;i++)
    {
    //For outer square
    LineDDA(X1, Y1, X1, Y1 + len);
    LineDDA(X1 , Y1+len, X1+len, Y1 + len);
    LineDDA(X1 +len, Y1+len, X1+len, Y1);
    LineDDA(X1, Y1, X1+len, Y1 );

    //For rhombus
    LineDDA(X1, Y1 + len/2, X1 + len/2, Y1 + len);
    LineDDA(X1+ len/2, Y1 + len, X1 + len, Y1 + len/2);
    LineDDA(X1+len, Y1 + len/2, X1 + len/2, Y1 );
    LineDDA(X1+len/2, Y1 , X1 , Y1 + len/2);

    //For innermost square

    LineDDA(X1+ len/4, Y1 + len/4, X1 + (3*len)/4, Y1 + len/4);
    LineDDA(X1 + (3*len)/4, Y1 + len/4, X1 + (3*len)/4, Y1 + (3*len)/4);
    LineDDA(X1 + (3*len)/4, Y1 + (3*len)/4, X1 + (len)/4, Y1 + (3*len)/4);
    LineDDA(X1 + (len)/4, Y1 + (3*len)/4, X1+ len/4, Y1 + len/4);

    X1=X1+len/4;
    Y1=Y1+len/4;
    len=len/2;
    }
    glFlush();
}
void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}
void reshap(int x,int y)
{
    glViewport(0.0,0.0,x,y);
    glutPostRedisplay();
}
int main(int iArgc, char** cppArgv) {
    cout<<"Enter x1 ,y1:";
    cin>>X1>>Y1;
    cout<<"Enter len:";
    cin>>len;
    cout<<"Enter times:";
    cin>>TIMES;
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Shubham");
	Initialize();
	glutReshapeFunc(reshap);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
