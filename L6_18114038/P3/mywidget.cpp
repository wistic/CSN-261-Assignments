/**
 * @file mywidget.cpp
 * @author Prathamesh Katkar
 * @brief print implementation for widget
 * @version 0.1
 * @date 2019-10-09
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "mywidget.h"
#include <sstream>

void MyWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QPen myPen(Qt::black, 1, Qt::SolidLine);
	QPen myPenDot(Qt::black, 7, Qt::SolidLine);
	for (int i = 0; i < segments.size(); i++)
	{
		auto [lx, ly, rx, ry] = segments[i];
		painter.setPen(myPen);

		painter.drawLine(lx, ly, rx, ry);
		stringstream ss;
		ss << " (" << lx << "," << ly << ")";
		string s = ss.str();
		painter.drawText(lx, ly, s.c_str());
		stringstream ss2;
		ss2 << " (" << rx << "," << rx << ")";
		string s2 = ss2.str();
		painter.drawText(rx, ry, s2.c_str());

		painter.setPen(myPenDot);
		painter.drawPoint(lx, ly);
		painter.drawPoint(rx, ry);
	}
	QPen myPen2(Qt::red, 7, Qt::SolidLine);
	painter.setPen(myPen2);
	for (int i = 0; i < points.size(); i++)
	{
		auto [x, y] = points[i];
		painter.drawPoint(x, y);
		stringstream ss;
		ss << " (" << x << "," << y << ")";
		string s = ss.str();
		painter.drawText(x, y, s.c_str());
	}

	QPen myPen3(Qt::blue, 7, Qt::DashLine);
	painter.setPen(myPen3);
	painter.drawLine(0, c, 1920.0f, 1920.0f * m + c);
	stringstream ss;
	ss << "Total intersecting points:" << points.size() << "  y=" << m << "x+"
	   << c;
	string s = ss.str();
	painter.drawText(0, 50, s.c_str());
}
