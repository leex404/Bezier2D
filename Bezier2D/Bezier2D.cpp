/// @Leexin
/// 2019-05-29
/// lixin1620@gmail.com
/// draw bezier curve

#include <iostream>
#include "Bezier2D.h"

#define MAX_POINTS_NUM  70  
//maximum number of point. can be more, but 70 is enough
using namespace std;

vector<int> x_loc = {};
vector<int> y_loc = {};
int height = 600;
int width  = 600;


void drawBezier_1(vector<int> x, vector<int> y, int num_of_points)
{
	float ax, bx;
	float ay, by;
	int temp_loc = x.size() - 2;

	glColor3f(0.0f, 0.0f, 1.0f);
	drawPixel(x[temp_loc + 0], y[temp_loc + 0], 7);
	drawPixel(x[temp_loc + 1], y[temp_loc + 1], 7);
	ax = x[temp_loc + 0];
	ay = y[temp_loc + 0];
	bx = x[temp_loc + 1];
	by = y[temp_loc + 1];

	float t;
	t = 0.0;
	float dt = 0.002;
	while (t <= 1)
	{
		float x_temp = (1 - t) * ax + t * bx;
		float y_temp = (1 - t) * ay + t * by;
		drawPixel(x_temp, y_temp, 1);
		t += dt;
	}
}

void drawBezier_2(vector<int> x, vector<int> y, int num_of_points)
{
	float ax, bx;
	float ay, by;
	float tSquared;
	int temp_loc = x.size() - 3;

	ax = x[temp_loc + 0] - 2 * x[temp_loc + 1] + x[temp_loc + 2];
	ay = y[temp_loc + 0] - 2 * y[temp_loc + 1] + y[temp_loc + 2];
	bx = x[temp_loc + 0] * (-2) + x[temp_loc + 1] * 2;
	by = y[temp_loc + 0] * (-2) + y[temp_loc + 1] * 2;

	glColor3f(0.0f, 0.0f, 1.0f);
	drawPixel(x[temp_loc + 0], y[temp_loc + 0], 7);
	drawPixel(x[temp_loc + 1], y[temp_loc + 1], 7);
	drawPixel(x[temp_loc + 2], y[temp_loc + 2], 7);

	float t;
	t = 0.0;
	float dt = 0.002;
	while (t <= 1)
	{
		tSquared = t * t;
		float x_temp = ax * tSquared + bx * t + x[temp_loc + 0];
		float y_temp = ay * tSquared + by * t + y[temp_loc + 0];
		drawPixel(x_temp, y_temp, 1);
		t += dt;
	}
}

void drawBezier_3(vector<int> x, vector<int> y, int num_of_points)
{
	float ax, bx, cx;
	float ay, by, cy;
	float tSquared, tCubed;
	int temp_loc = x.size() - 4;

	cx = 3.0 * (x[temp_loc + 1] - x[temp_loc + 0]);
	bx = 3.0 * (x[temp_loc + 2] - x[temp_loc + 1]) - cx;
	ax = x[temp_loc + 3] - x[temp_loc + 0] - cx - bx;

	cy = 3.0 * (y[temp_loc + 1] - y[temp_loc + 0]);
	by = 3.0 * (y[temp_loc + 2] - y[temp_loc + 1]) - cy;
	ay = y[temp_loc + 3] - y[temp_loc + 0] - cy - by;

	glColor3f(0.0f, 0.0f, 1.0f);
	drawPixel(x[temp_loc + 0], y[temp_loc + 0], 7);
	drawPixel(x[temp_loc + 1], y[temp_loc + 1], 7);
	drawPixel(x[temp_loc + 2], y[temp_loc + 2], 7);
	drawPixel(x[temp_loc + 3], y[temp_loc + 3], 7);

	float t;
	t = 0.0;
	float dt = 0.002;
	while (t <= 1)
	{
		tSquared = t * t;
		tCubed = tSquared * t;
		float x_temp = (ax * tCubed) + (bx * tSquared) + (cx * t) + x[temp_loc + 0];
		float y_temp = (ay * tCubed) + (by * tSquared) + (cy * t) + y[temp_loc + 0];
		drawPixel(x_temp, y_temp, 1);
		t += dt;
	}
}

double fac(int n)  // 阶乘
{
	double result = 1;
	if (n == 0)
		return result;
	for (int i = 1; i <= n; i++){
		result *= i;
	}
	return result;
}

double combinate(int n, int k) //组合数
{
	if (k == 0)
		return 1;
	double result = 0;
	result = fac(n) / (fac(k)*(fac(n - k)));
	return result;
}


void drawBezier(vector<int> x, vector<int> y, int num_of_points) {
	
	float px = 0.0, py = 0.0; //point current should draw
	int n;        //number of points -1
	float t = 0.0, dt = 0.0005; //t in [0, 1], dt is changes each time in t
	n = x.size() - 1;
	while (t <= 1) {
		for (int i = 0; i <= n; i++) {
			double temp = combinate(n, i)*powf(t, i)*powf(1 - t, n - i);
			px += temp * x[i];
			py += temp * y[i];
		}
		drawPixel(px, py, 1);
		t += dt;
		px = 0.0;
		py = 0.0;
	}
}

void drawPixel(int x, int y, int point_size)
{
	//glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(point_size);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void Display()
{
	//重新设置OpenGL窗口：原点位置为左上角，x轴从左到右，y轴从上到下，坐标值与像素坐标值相同
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);

	if (x_loc.size() > 0){
		drawPixel(x_loc[x_loc.size()-1], y_loc[x_loc.size() - 1], 7);
		glColor3f(171.0 / 255.0f, 98.0 / 255.0f, 180.0/255.0f);
		if (x_loc.size() < MAX_POINTS_NUM )//&& x_loc.size() <= 30)//MAX_POINTS_NUM)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for(int i = 0; i < x_loc.size(); i++)
				drawPixel(x_loc[i], y_loc[i], 7);
			glColor3f(44.0 / 255.0f, 163.0 / 255.0f, 1.0f);
			drawBezier(x_loc, y_loc, x_loc.size());
		}
		/*
		if (x_loc.size() % 4 == 0){ //3阶曲线
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3f(44.0 / 255.0f, 163.0 / 255.0f, 1.0f);
			drawBezier_3(x_loc, y_loc, 4);
		}
		if (x_loc.size() % 3 == 0) {//2阶曲线
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3f(44.0 / 255.0f, 163.0 / 255.0f, 1.0f);
			drawBezier_2(x_loc, y_loc, 3);
		}
		if (x_loc.size() % 2 == 0) {//1阶曲线
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3f(44.0 / 255.0f, 163.0 / 255.0f, 1.0f);
			drawBezier_1(x_loc, y_loc, 2);
		}
		*/
	}
	glutSwapBuffers(); 
	glutPostRedisplay();
}

void Mouse_hit(int button, int state, int x, int y)
{
	/// state == 1 mean button up
	/// state == 0 mean button down
	/// button == 0 mean left button
	/// button == 1 mean middle button
	/// button == 2 mean right button
	/// [x, y] is the location of mouse pointer

	if (button == 0 && state == 1)
	{
		x_loc.push_back(x);
		y_loc.push_back(y);
		cout << "point location: " << x_loc[x_loc.size() - 1] << " " << y_loc[y_loc.size() - 1] << endl;
	}
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, 1.0, -1.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//double buffers && RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bezier 2D");
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse_hit);
	glutReshapeFunc(ChangeSize);
	glClearColor(30.0/255.0f, 30.0 / 255.0f, 30.0 / 255.0f, 0.2f); // background color
	glColor3f(44.0/255.0f, 163.0/255.0f, 1.0f);
	glutMainLoop();

	return 0;
}