#pragma once
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <Windows.h>
#include <math.h>
using namespace std;
void drawPixel(double x, double y, int);
void drawBezier_1(vector<int> x, vector<int> y, int num_of_points);
void drawBezier_2(vector<int> x, vector<int> y, int num_of_points);
void drawBezier_3(vector<int> x, vector<int> y, int num_of_points);
double fac(int n);
double combinate(int n, int k);
void drawBezier(vector<int> x, vector<int> y, int num_of_points);


// curve below 3rd order

