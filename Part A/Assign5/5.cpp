/*5.Draw a 4X4 chessboard rotated 45 degrees with the horizontal axis.
    Use Bresenham algorithm to draw all the lines.
    Use seed fill algorithm to fill black squares of the rotated chessboard
*/

#include<iostream>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265

using namespace std;

//globals

int width=600;
int height=600;


//-----COLOR---
struct Color{
GLfloat R;
GLfloat G;
GLfloat B;
bool operator!=(Color);
};

bool Color::operator!=(Color c)
{
    if( c.R != this->R )
        return true;
    if( c.G != this->G )
        return true;
    if( c.B != this->B )
        return true;
    return false;
}

// functions for line generation
int sign(int a)
{
    if(a>0)
        return 1;
    if(a<0)
        return -1;
    return 0;
}
void bres(int x1,int y1,int x2,int y2)
{
    int e,s1,s2,x,y,dx,dy;
    bool interchange;
    x = x1;y = y1;
    dx = abs( x2 - x1 );
    dy = abs( y2 - y1 );
    s1 = sign(x2-x1);
    s2 = sign(y2-y1);
    if(dy > dx)
    {
        interchange = true;
        //swap
        dx = dx + dy;
        dy = dx - dy;
        dx = dx - dy;
    }else{
    interchange = false;
    }
    e = 2*dy - dx;
    for(int i=0;i <= dx;i++)
    {

        glVertex2i(x,y);
        while(e>0)
        {
            if(interchange)
                x += s1;
            else
                y += s2;
            e = e - 2*dx;
        }
        if(interchange)
            y += s2;
        else
            x += s1;
        e = e + 2*dy;
    }
}
void seed_fill(int x,int y,Color newcol)
{
    Color old;
    glReadPixels((x+100)*(width/200), (y+100)*(width/200), 1, 1, GL_RGB, GL_FLOAT, &old);//pls dont put me in glbegin and glend!!
    if(old!=newcol)
    {

        glBegin(GL_POINTS);
        glVertex2i(x,y);
         glEnd();

        seed_fill(x-1,y,newcol);
        seed_fill(x+1,y,newcol);
        seed_fill(x,y-1,newcol);
        seed_fill(x,y+1,newcol);
    }
}
void Draw()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(45,0,0,1);
        glColor3f(0.0,0.0,0.0);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        //lines
        for(int i=-70;i<=70;i+=35)
        {
            bres(i,-70,i,70);//verticals
            bres(-70,i,70,i);//horizontals
        }
        Color c;
        c.R=0.0f;
        c.G=0.0f;
        c.B=0.0f;
        glEnd();
        glFlush();
        glRotatef(-45,0,0,1);
        int x,y;
        for(int k=0;k<=35;k+=35)
        for(int x1=-53+k;x1<70;x1+=70)
            for(int y1=-53+k;y1<70;y1+=70)
            {
                x = (x1*cos(PI/4))-(y1*sin(PI/4));
                y = (x1*sin(PI/4))+(y1*cos(PI/4));
                seed_fill(x,y,c);
            }

        glFlush();
}
void Initialize() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}
void reshap(int x,int y)
{
    width=x;
    height=y;
    glViewport(0.0,0.0,x,y);
    glutPostRedisplay();
}
//--------MAIN--------------------------
int main(int iArgc, char** cppArgv) {

	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width,height);//read pixel wale
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window ");

	Initialize();
	glutReshapeFunc(reshap);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
