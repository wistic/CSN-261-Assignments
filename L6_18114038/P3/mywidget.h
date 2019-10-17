/**
 * @file mywidget.h
 * @author Prathamesh Katkar
 * @brief header file for widget
 * @version 0.1
 * @date 2019-10-09
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once

#include <QWidget>
#include <QtGui>
#include <tuple>
#include <vector>
using namespace std;
class MyWidget : public QWidget
{
	Q_OBJECT
public:
	vector<tuple<float, float>> points;
	vector<tuple<float, float, float, float>> segments;
	float m;
	float c;

protected:
	/**
 * @brief Event to draw to screen
 *
 * @param event
 */
	void paintEvent(QPaintEvent *event);
signals:

public slots:
};
