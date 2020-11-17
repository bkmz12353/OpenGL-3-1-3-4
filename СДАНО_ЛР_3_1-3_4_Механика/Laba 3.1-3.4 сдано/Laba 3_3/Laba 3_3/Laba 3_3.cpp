
#include <iostream>
#include <windows.h>
#include <glut.h> //Подключение библиотеки glut.h
#include <gl/GLU.h>
#include <stdlib.h>
#include <gl/GL.h>
#include <cmath>

using namespace std;

double ro = 1.29;
double g = 9.8;
double dt = 0.1;
double c = 0.45;
double b = 0.00129;
double F;
double s = 20;
double alpha;
double m0;
double mk;
double k;
double m, a, v, h, t;
//Рисует траекторию тела брошенного под
//углом к горизонту с учетом сопритивления среды
void render_scene() {
	//Очищает текущим цветом
	glClear(GL_COLOR_BUFFER_BIT);
	//Рисует координатную систему
	//Задает цвет рисовки красным
	glLineWidth(4.0);
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(1.4, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 1.4);
	glEnd();
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	float i;
	for (i = 0; i <= 1.3; i = i + 0.25) {
		glBegin(GL_LINES);
		glVertex2f(1.0, i);
		glVertex2f(1.0, i + 0.1);
		glEnd();
	}
	for (i = 0; i <= 1.3; i = i + 0.25) {
		glBegin(GL_LINES);
		glVertex2f(i, 1.0);
		glVertex2f(i + 0.1, 1.0);
		glEnd();
	}
	cout << "F = "; cin >> F;
	cout << "m0: "; cin >> m0;
	cout << "mk: "; cin >> mk;
	cout << "alpha: "; cin >> alpha;
	cout << "k = "; cin >> k;
	for (i = 0; i <= k; i = i + 1) {
		F = F + F * 0.5;
		v = 0;
		h = 0;
		t = dt;
		double tk = ((m0 - mk) / alpha);
		glColor3d(i / 10.0, 1.0 - i / 10.0, 1.0);
		glBegin(GL_POINTS);
		while ((t <= tk) && (v <= 1.0)) {
			m = m0 - alpha * t;
			a = (F - m * g - (1 / 2) * c * ro * exp(-b * h) * s * v * v) / m;
			v = v + a * dt / 7800;
			h = h + v * dt;
			glVertex2d(t / tk, v);
			t += dt;
		}
		glEnd();
		glutSwapBuffers();
	}
}
void change_size(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(5, 5, w, h);
	gluOrtho2D(0, 1.5, 0, 1.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Initialise() {
	//Цвет очистки черный
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
int main(int argc, char** argv) {
	//Создание окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Полет ракеты");
	//Вызывание обратных функций
	glutDisplayFunc(render_scene);
	glutReshapeFunc(change_size);
	Initialise();
	//initMenu();
	//Запустить оболочку GLUT
	glutMainLoop();
	return 0;
}
