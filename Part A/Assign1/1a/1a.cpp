/* 1. A Mandelbrot Set is a set of complex number
     z that does not diverge under the transformation
      (x)n+1= (x)n^2+ z with (x)0=0.
     Where, both x and z represent the complex numbers.
    a)Plot the Mandelbrot set for the threshold |x|= 2.
main.cpp -lGL -lGLU -lglut
*/
#include<iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;
float max_iteration = 20.0f;
float x1=-2.0f;
float x2=2.0f;
float y12=-2.0f;
float y2=2.0f;
float reso=0.001f;
struct complex{
    float real;
    float imag;
};
void disp()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0f);
	glBegin(GL_POINTS);

    float temp,r,g,b,iteration ;
	complex c,z,t;
    for(float row = x1; row < x2; row+=reso){
        for(float column = y12; column <y2; column+=reso){
        iteration=0.0f;
        c.real=row;
        c.imag=column;
        z.real=0;
        z.imag=0;

                while(((((z.real*z.real)+(z.imag*z.imag))) < 4.0f) &&( ++iteration < max_iteration))
                {
                    t=z;
                    //z=z^2+c
                    z.real =(float) (t.real*t.real)-(t.imag*t.imag) + c.real;
                    z.imag =(float)  (2.0f*t.real*t.imag)+ c.imag;
                }

        if(iteration>=(max_iteration-0.1f))
        {
            glColor3f(0,0,0);
        }else{
            temp=(float)iteration/max_iteration;
            //temp=0.0----1.0
            temp=temp*7.0f;
            //temp=0.0----7.0
            b =fmod(temp,2);
            temp=temp/2;
            r = fmod(temp,2);
            temp=temp/2;
            g = fmod(temp,2);
            glColor3f(b,g,r);
         }
         glVertex3f((row+(-x1))/((-1.0f*x1)+x2),(column+(-y12))/((-1.0f*y12)+y2),0);
         //cout<<(row+(-x1))/((-1.0f*x1)+x2)<<endl;
		}
	}
	glEnd();
    glFlush();
}

void init()
{

    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}
void key(unsigned char key,int x,int y)
{
    static float rrr=0.1f;
    switch(key)
    {
        //----------zoom--------------
    case 'z':
        x1+=rrr;
        x2-=rrr;
        y12+=rrr;
        y2-=rrr;
        rrr=rrr/1.0009f;
        //cout<<x1<<"  "<<"x2"<<x2<<endl;
        glutPostRedisplay();
        break;
    case 'u':
         x1-=rrr;
        x2+=rrr;
        y12-=rrr;
        y2+=rrr;
        rrr=rrr*1.00005f;
        glutPostRedisplay();
        break;
        //---------move---------------
    case'w':
        y12+=rrr;
        y2+=rrr;
        glutPostRedisplay();
        break;
        case's':
        y12-=rrr;
        y2-=rrr;
        glutPostRedisplay();
        break;
        case'a':
        x1-=rrr;
        x2-=rrr;
        glutPostRedisplay();
        break;
        case'd':
        x1+=rrr;
        x2+=rrr;
        glutPostRedisplay();
        break;
  

    }
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200,650);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Shubham");
	glutDisplayFunc(disp);
	glutKeyboardFunc(key);
    init();
	glutMainLoop();
	return 0;
}
