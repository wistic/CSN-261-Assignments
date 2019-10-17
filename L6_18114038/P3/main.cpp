/**
 * @file main.cpp
 * @author Prathamesh Katkar
 * @brief main file to launch the window
 * @version 0.1
 * @date 2019-10-09
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "bentley-ottmann.h"
#include "mywidget.h"
#include <QApplication>
#include <iostream>
#include <tuple>

using namespace std;

/**
 * @brief gets the m and c values for somes point
 *
 * @param points
 * @return tuple<float, float>
 */
tuple<float, float> linearFit(vector<tuple<float, float>> &points)
{
	float sumx = 0, sumx2 = 0, sumy = 0, sumyx = 0, b, a;
	for (int i = 0; i < points.size(); i++)
	{
		auto [x, y] = points[i];
		sumx = sumx + x;
		sumx2 = sumx2 + x * x;
		sumy = sumy + y;
		sumyx = sumyx + y * x;
	}
	b = (sumx2 * sumy - sumyx * sumx) / (points.size() * sumx2 - sumx * sumx);
	a = (points.size() * sumyx - sumx * sumy) /
		(points.size() * sumx2 - sumx * sumx);
	return {a, b};
}

/**
 * @brief main function for program
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
	int total;
	cin >> total;
	vector<Point> intersections;
	vector<Segment> segments;
	vector<tuple<float, float, float, float>> segs;
	for (int i = 0; i < total; i++)
	{
		float lx, ly, rx, ry;
		cin >> lx >> ly >> rx >> ry;
		segments.push_back(Segment(Point(lx, ly), Point(rx, ry)));
		segs.push_back(tuple(lx, ly, rx, ry));
	}
	intersect(segments, intersections);

	QApplication a(argc, argv);
	MyWidget myWidget;
	cout << "points" << intersections.size() << endl;
	for (int i = 0; i < intersections.size(); i++)
	{
		myWidget.points.push_back(
			tuple((float)intersections[i].x, (float)intersections[i].y));
		cout << "(" << intersections[i].x << ", " << intersections[i].y << ")"
			 << endl;
	}

	for (int i = 0; i < segs.size(); i++)
	{
		myWidget.segments.push_back(segs[i]);
	}

	auto [m, c] = linearFit(myWidget.points);
	myWidget.m = m;
	myWidget.c = c;
	cout << "y=" << m << "x+" << c << endl;
	myWidget.show();
	myWidget.setFixedSize(1920, 1080);
	return a.exec();
}
