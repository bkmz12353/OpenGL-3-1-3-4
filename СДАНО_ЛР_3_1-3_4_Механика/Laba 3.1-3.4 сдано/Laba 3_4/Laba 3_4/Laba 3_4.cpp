
#include <iostream>
#include <windows.h>
#include <glut.h> //Подключение библиотеки glut.h
#include <gl/GLU.h>
#include <stdlib.h>
#include <gl/GL.h>
#include <cmath>

using namespace std;

float x = 1.2;
//y - координата спутник
//Она поначалу равна 0
float y = 0;
//vx - Составляющие скорости по Ох
//Эта скорость в начальный момент времени равна 0
double vx = 0;
//vy - составляющее скорости по Оу
//Она в начальный момент времени равна 1.2
double vy = 1.2;
//dt - шаг
double dt = 0.00005;
//t - Общее время
double t = dt;
//PI - число Пи
const double PI = 3.1415926535;
//m,k - Промедуточные переменные
double m, k;
double velo(double v, double z, double l, double ta) {
	m = z * z + l * l;
	k = sqrt(m);
	return (v - (z / (k * k * k) * ta));
}
//Вызывается при изменении размеров окна
void change_size(GLsizei w, GLsizei h) {
	GLdouble aspect_ratio;
	//Предотвращает деление на 0
	if (h == 0)
		h = 1;
	//Устанавливает поле просмотра с размерами окна
	glViewport(0, 0, w, h);
	//Обновляет систему координат
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//С помощью плоскостей отсечения (левая, правая, нижняя,
	//верхная, ближная, далняя) устанавливает объем
	aspect_ratio = (GLdouble)w / (GLdouble)h;
	if (w <= h)
		glOrtho(-40.0, 6.0, -23.0 / aspect_ratio, 23.0 /
			aspect_ratio, -1.0, 1.0);
	else
		glOrtho(-40.0 * aspect_ratio, 6.0 * aspect_ratio, -
			23.0, 23.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//Задает состояние визуализации
void initialise() {
	//Задает цвет очистки окна
	//Цвет очистки - черный
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
void render_scene() {
	//Очищает окно, изпользуя текущий цвет очистки
	glClear(GL_COLOR_BUFFER_BIT);
	//В качестве текущего цвета рисования задает красный
	//R G B
	glColor3f(1.0, 0.0, 0.0);
	//Рисует координатную систему:
	//Рисует ось Ох
	glBegin(GL_LINES);
	glVertex2f(-39.0, 0.0);
	glVertex2f(5.0, 0.0);
	glEnd();
	//Рисует ось Оу
	glBegin(GL_LINES);
	glVertex2f(0.0, -22.0);
	glVertex2f(0.0, 22.0);
	glEnd();
	//Рисуем центр притяжения
	//Радиус центра равна 1
	//Цвет рисовки - зеленый
	glColor3f(0.0, 1.0, 0.0);
	double radian = 0.0;
	double xx, yy;
	glBegin(GL_POINTS);
	while (radian <= 2 * PI) {
		xx = cos(radian);
		yy = sin(radian);
		glVertex2d(xx, yy);
		radian += 0.05;
	}
	glEnd();
	//Задает в качества цвета рисовки синий
	glColor3f(0.0, 0.0, 1.0);
	//Рисуем траектерию первого спутника
	glBegin(GL_POINTS);
	while (t <= 70) {
		glVertex2d(x, y);
		vx = velo(vx, x, y, dt);
		vy = velo(vy, y, x, dt);
		x += vx * dt;
		y += vy * dt;
		t += dt;
	}
	glEnd();
	//Задает начальные данные
	x = 1.25;
	y = 0;
	vx = 0;
	vy = 1.2;
	t = 0;
	//Рисуем траекторию второго спутника
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	while (t <= 200) {
		glVertex2d(x, y);
		vx = velo(vx, x, y, dt);
		vy = velo(vy, y, x, dt);
		x += vx * dt;
		y += vy * dt;
		t += dt;
	}
	glEnd();
	//Рисуем траекторию 3-го спутника
	x = 1.3;
	y = 0;
	vx = 0;
	vy = 1.2;
	t = 0;
	glColor3f(.5, .6, 1.0);
	glBegin(GL_POINTS);
	while (t <= 220) {
		glVertex2d(x, y);
		vx = velo(vx, x, y, dt);
		vy = velo(vy, y, x, dt);
		x += vx * dt;
		y += vy * dt;
		t += dt;
	}
	glEnd();
	//Очищает очередь текущих команд
	glFlush();
}
//Точка входа основной программы
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//Задает размер окна
	glutInitWindowSize(640, 640);
	//Определяет позиции окна на рабочем столе
	glutInitWindowPosition(20, 20);
	//Создает окно с названием в кавычках
	glutCreateWindow("Движение небесных тел");
	//Дисплейная функция
	glutDisplayFunc(render_scene);
	//Функция перерисовки
	glutReshapeFunc(change_size);
	initialise();
	//Запускает оболочку GLUT
	glutMainLoop();
	return 0;
}
