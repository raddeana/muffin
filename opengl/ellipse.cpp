#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159f
#define R1 5
#define R2 8
#define n 100

GLfloat theta = 0.0f;

void init () {
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);

	// glLoadIdentity();
	gluOrtho2D(-10, 20, -10, 20);
}
 
void display () {
	// GLfloat x, y
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
  glBegin(GL_LINES);
	glVertex2f(-10, 5);
	glVertex2f(20, 5);
	glVertex2f(5, 20);
	glVertex2f(5,-20);
	glEnd();
	
	glPointSize(5);
	glBegin(GL_POINTS);
	
  for (int i = 0; i < n; i ++) {
		glVertex2f(R1 * cos(2 * PI / n * i),R2 * sin(2*PI / n*i));
	}
  
  glEnd();
	glFlush();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("hello");
	
  init();
  
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
