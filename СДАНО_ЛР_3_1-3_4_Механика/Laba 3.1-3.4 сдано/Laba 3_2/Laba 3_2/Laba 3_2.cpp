
#include <iostream>
#include <windows.h>
#include <glut.h> //Подключение библиотеки glut.h
#include <gl/GLU.h>
#include <stdlib.h>
#include <gl/GL.h>
#include <cmath>


double x;
const double pi = 3.1415;
double A;
double B;
double a = 30;
double Y[4], y[4];
double h = 0.00001, hpr = 0.0001;
double Ff(int i, double* x, double* y) {
	switch (i)
	{
	case 0:
		return (-A * sin(a) * y[0] - B * sin(a) * sqrt(y[0] * y[0]
			+ y[1] * y[1]) * y[0]);
		break;
	case 1:
		return (-sin(a) - A * sin(a) * y[0] -
			B * sin(a) * sqrt(y[0] * y[0] + y[1] * y[1]) * y[1]);
		break;
	case 2:
		return (y[0] / (2 * cos(a)));
		break;
	case 3:
		return (2 * y[1] / sin(a));
		break;
	}
}
//Вычисление правой части дифференциального уравнения
void RightDiff(double* x, double* y, double* g) {
	int i;
	for (i = 0; i < 4; i++)
		g[i] = Ff(i, x, y);
}
//Реализация алгоритма Рунге-Кутте
void runge_kutte(double* x, double* y0, double* y, double h) {
	int i;
	double z[4], k1[4], k2[4], k3[4], k4[4];
	RightDiff(x, y0, k1); *x = *x + h / 2;
	for (i = 0; i < 4; i++)
		z[i] = y0[i] + h * k1[i] / 2;
	RightDiff(x, z, k2);
	for (i = 0; i < 4; i++)
		z[i] = y0[i] + h * k2[i] / 2;
	RightDiff(x, z, k3); *x = *x + h / 2;
	for (i = 0; i < 4; i++)
		z[i] = y0[i] + h * k3[i] / 2;
	RightDiff(x, z, k4);
	for (i = 0; i < 4; i++)
		y[i] = y0[i] + h * (k1[i] + 2 * k2[i] + 2 * k3[i] +
			k4[i]) / 6;
	RightDiff(x, z, k2);
}
//Рисует траекторию тела брошенного под
//углом к горизонту с учетом сопритивления среды
void render_scene() {
	//Очищает текущим цветом
	glClear(GL_COLOR_BUFFER_BIT);
	//Рисует координатную систему
	//Задает цвет рисовки красным
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(2.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 2.0);
	glEnd();
	A = 0.5;
	B = 0.04;
	double x0 = 0;
	x = x0;
	y[3] = Y[3];
	int i;
	//Рисует траекторию
	int j;
	for (j = 1; j <= 4; j++) {
		A *= j;
		B *= j;
		//Переводит уголь из градуса в радианы
		a *= pi / 180.0;
		//Начальная скорость по оси Ох
		Y[0] = cos(a);
		//Начальная скорость по оси Оу
		Y[1] = sin(a);
		//Начальная координата х
		Y[2] = 0;
		//Начальная координата у
		Y[3] = 0;
		//Задает цвет рисовки
		glColor3f(1 - 0.4 / j, 0.4 / j, 0.4 + 0.4 / j);
		x0 = 0;
		x = x0;
		y[3] = Y[3];
		glBegin(GL_POINTS);
		while (y[3] >= 0.0) {
			runge_kutte(&x, Y, y, h);
			for (i = 0; i < 4; i++)
				Y[i] = y[i];
			//Рисовать в двухмерном пространстве точку
			//в указанной координате
			glVertex2d(Y[2], Y[3]);
		}
		glEnd();
	}
	glutSwapBuffers();
}
void change_size(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(5, 5, w, h);
	gluOrtho2D(0, 2.0, 0, 2.0);
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
	glutCreateWindow("С учетом сопротивления");
	//Вызывание обратных функций
	glutDisplayFunc(render_scene);
	glutReshapeFunc(change_size);
	Initialise();
	//initMenu();
	//Запустить оболочку GLUT
	glutMainLoop();
	return 0;
}