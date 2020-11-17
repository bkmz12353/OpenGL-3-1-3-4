
#include <iostream>
#include <cmath>
#include <windows.h>
#include <glut.h> //Подключение библиотеки glut.h
#include <gl/GLU.h>
#include <stdlib.h>
#include <gl/GL.h>

const double PI = 3.1415;
float V = 20.0f;
float alpha = 30;
double cx, cy;
int m;
const double g = 9.8;
void render_scene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(.0, .0);
	glVertex2f(cx, .0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.0, .0);
	glVertex2f(.0, cy);
	glEnd();
	//Изменение цвета рисовки
	glColor3f(0.1, 0.8, 0.4);
	double x = 0.0, y;
	alpha *= PI / 180.0;
	double t = .0;
	glBegin(GL_POINTS);
	while (t <= (V * sin(alpha) / g))
	{
		x = V * cos(alpha) * t;
		y = V * sin(alpha) * t - g * t * t / 2;
		glVertex2d(x, y);
		t += 0.01;
	}
	double h = y;
	double l = x;
	t = 0.0;
	while (t <= (V * sin(alpha) / g))
	{
		x = l + V * cos(alpha) * t;
		y = h - g * t * t / 2;
		glVertex2d(x, y);
		t += 0.01;
	}
	glEnd();
	glutSwapBuffers();
}
void change_size(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	cx = V * V * sin(2 * (alpha * PI / 180.0)) / g + 15;
	cy = V * V * sin(alpha * PI / 180.0) * sin(alpha * PI / 180.0) /
		(2 * g) + 15;
	glViewport(5, 5, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, cx, 0.0, cy);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Initialise() {
	glClearColor(0, 0, 0, 0);
}
void check_menu(int v) {
	if (v = 0)
		glutSetWindowTitle("Hi");
}
void checkS2menu(int v) {
	switch (v)
	{
	case 6:
		alpha = 30;
		glutPostRedisplay();
		break;
	case 7:
		alpha = 45;
		glutPostRedisplay();
		break;
	case 8:
		alpha = 60;
		glutPostRedisplay();
		break;
	}
}
void initialMenu() {
	int SM2 = glutCreateMenu(checkS2menu);
	glutSetMenu(SM2);
	glutAddMenuEntry("30 градусов", 6);
	glutAddMenuEntry("45 градусов", 7);
	glutAddMenuEntry("60 градусов", 8);
	int M = glutCreateMenu(check_menu);
	glutSetMenu(M);
	glutAddSubMenu("Уголь равен", SM2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(480, 360);
	glutInitWindowPosition(40, 60);
	glutCreateWindow("Без сопротивления");
	glutDisplayFunc(render_scene);
	glutReshapeFunc(change_size);
	Initialise();
	initialMenu();
	glutMainLoop();
	return 0;
}
