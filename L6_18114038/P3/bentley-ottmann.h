/**
 * @file bentley-ottmann.h
 * @author Utkarsh
 * @brief implementation of bently sweep algo
 * @version 0.1
 * @date 2019-10-09
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <vector>

/**
 * @brief Struct to represent a point
 *
 */
struct Point
{
	double x, y;
	Point &operator=(Point const &b)
	{
		x = b.x;
		y = b.y;
		return *this;
	}
	Point(const Point &b) : x(b.x), y(b.y) {}
	Point(double _x, double _y) : x(_x), y(_y) {}
	bool operator<(const Point &b) const
	{
		if (y < b.y - 1.0e-9)
			return true;
		else if (y > b.y + 1.0e-9)
			return false;
		else if (x < b.x - 1.0e-9)
			return true;
		else
			return false;
	}
	bool operator==(const Point &b) const
	{
		return fabs(y - b.y) < 1.0e-9 && fabs(x - b.x) < 1.0e-9;
	}
	bool operator!=(const Point &b) const
	{
		return fabs(y - b.y) > 1.0e-9 || fabs(x - b.x) > 1.0e-9;
	}
};

/**
 * @brief Struct to represent a line segment
 *
 */
struct Segment
{
	Point beg, end;
	Segment &operator=(Segment const &b)
	{
		beg = b.beg;
		end = b.end;
		return *this;
	}
	Segment(const Segment &b) : beg(b.beg), end(b.end) {}
	Segment(const Point &_beg, const Point &_end) : beg(_beg), end(_end) {}
};

#define SEG_START 0
#define SEG_END 1

/**
 * @brief class to represent a sweep event
 *
 */
class event_less
{
public:
	bool operator()(const std::pair<double, int> &a,
					const std::pair<double, int> &b) const
	{
		if (a.first < b.first - 1.0e-9)
			return true;
		else if (a.first > b.first + 1.0e-9)
			return false;
		else if (a.second < b.second)
			return true;
		return false;
	}
};

/**
 * @brief segment intersection test between 2 segments
 *
 * @param a
 * @param b
 * @return std::pair<bool, Point>
 */
std::pair<bool, Point> intersect(const Segment &a,
								 const Segment &b)
{
	Point ret(0, 0);
	double div = (a.beg.x - a.end.x) * (b.beg.y - b.end.y) -
				 (a.beg.y - a.end.y) * (b.beg.x - b.end.x),
		   t;
	if (fabs(div) < 1.0e-13)
	{
		return std::make_pair(false, ret);
	}
	ret.x = ((a.beg.x * a.end.y - a.beg.y * a.end.x) * (b.beg.x - b.end.x) -
			 (a.beg.x - a.end.x) * (b.beg.x * b.end.y - b.beg.y * b.end.x)) /
			div;
	ret.y = ((a.beg.x * a.end.y - a.beg.y * a.end.x) * (b.beg.y - b.end.y) -
			 (a.beg.y - a.end.y) * (b.beg.x * b.end.y - b.beg.y * b.end.x)) /
			div;
	if (fabs(a.end.x - a.beg.x) > 1.0e-9)
	{
		t = (ret.x - a.beg.x) / (a.end.x - a.beg.x);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)
		{
			return std::make_pair(false, ret);
		}
	}
	if (fabs(a.end.y - a.beg.y) > 1.0e-9)
	{
		t = (ret.y - a.beg.y) / (a.end.y - a.beg.y);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)
		{
			return std::make_pair(false, ret);
		}
	}
	if (fabs(b.end.x - b.beg.x) > 1.0e-9)
	{
		t = (ret.x - b.beg.x) / (b.end.x - b.beg.x);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)
		{
			return std::make_pair(false, ret);
		}
	}
	if (fabs(b.end.y - b.beg.y) > 1.0e-9)
	{
		t = (ret.y - b.beg.y) / (b.end.y - b.beg.y);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)
		{
			return std::make_pair(false, ret);
		}
	}

	return std::make_pair(true, ret);
}

/**
 * @brief internal implementation of algo
 *
 * @param a
 * @param b
 * @param I
 * @param segments
 * @param sweep
 * @param events
 */
void intersect(int a,
			   int b,
			   const Point &I,
			   std::vector<Segment> &segments,
			   std::multimap<Point, int> &sweep,
			   std::multimap<std::pair<double, int>, int, event_less> &events)
{
	{
		int rem_end_events[2];
		rem_end_events[0] = a;
		rem_end_events[1] = b;
		for (int k = 0; k < 2; ++k)
		{
			std::pair<std::multimap<std::pair<double, int>, int,
									event_less>::iterator,
					  std::multimap<std::pair<double, int>, int,
									event_less>::iterator>
				del = events.equal_range(std::make_pair(
					segments[rem_end_events[k]].end.x,
					SEG_END));
			bool flag = false;
			for (std::multimap<std::pair<double, int>, int,
							   event_less>::iterator it = del.first;
				 it != del.second; ++it)
			{
				if (it->first.second == SEG_END &&
					it->second ==
						rem_end_events[k])

				{
					events.erase(it);
					flag = true;
					break;
				}
			}
			if (!flag)
				std::cout << "Cannot find proper ending event for segment"
						  << std::endl;
		}
	}

	segments.push_back(Segment(I, segments[a].end));

	events.insert(std::make_pair(std::make_pair(I.x, SEG_START),
								 (int)segments.size() - 1));

	events.insert(std::make_pair(std::make_pair(segments.back().end.x, SEG_END),
								 (int)segments.size() - 1));

	segments[a].end = I;

	events.insert(std::make_pair(std::make_pair(I.x, SEG_END), a));

	segments.push_back(Segment(I, segments[b].end));

	events.insert(std::make_pair(std::make_pair(I.x, SEG_START),
								 (int)segments.size() - 1));

	events.insert(std::make_pair(std::make_pair(segments.back().end.x, SEG_END),
								 (int)segments.size() - 1));

	segments[b].end = I;

	events.insert(std::make_pair(std::make_pair(I.x, SEG_END), b));
}

/**
 * @brief exposed interface to use the algorithm
 *
 * @param segments
 * @param intersections
 */
void intersect(std::vector<Segment> &segments,
			   std::vector<Point> &intersections)
{
	std::multimap<std::pair<double, int>, int, event_less> events;
	std::multimap<Point, int> sweep;

	for (int k = 0; k < (int)segments.size(); ++k)
	{
		if (segments[k].beg.x > segments[k].end.x)
			std::swap(segments[k].beg, segments[k].end);
		events.insert(
			std::make_pair(std::make_pair(segments[k].beg.x, SEG_START), k));
		events.insert(
			std::make_pair(std::make_pair(segments[k].end.x, SEG_END), k));
	}

	while (!events.empty())
	{
		std::multimap<std::pair<double, int>, int, event_less>::iterator first =
			events.begin();
		int t = first->first.second;
		int s = first->second;
		events.erase(first);
		if (t == SEG_START)
		{
			std::multimap<Point, int>::iterator ins =
				sweep.insert(std::make_pair(segments[s].beg, s));
			for (int dir = 0; dir <= 1; ++dir)
			{
				std::multimap<Point, int>::iterator iter = ins;
				while ((dir ? ++iter : iter--) !=
					   (dir ? sweep.end()
							: sweep.begin()))
				{
					if (segments[s].beg !=
						segments[iter->second]
							.beg)
					{
						std::pair<bool, Point> I = intersect(
							segments[s], segments[iter->second]);
						if (I.first)
						{
							intersections.push_back(I.second);
							intersect(s, iter->second, I.second, segments,
									  sweep, events);
						}
					}
					if ((2 * dir - 1) * (iter->first.y - ins->first.y) >
						0)
						break;
				}
			}
		}
		else if (t == SEG_END)
		{

			std::pair<std::multimap<Point, int>::iterator,
					  std::multimap<Point, int>::iterator>
				range = sweep.equal_range(segments[s].beg);
			std::multimap<Point, int>::iterator above = range.second,
												below = range.first;
			bool flag = false, test = true;
			if (below-- == sweep.begin())
				test = false;
			if (above == sweep.end())
				test = false;
			for (std::multimap<Point, int>::iterator it = range.first;
				 it != range.second; ++it)
			{
				if (it->second == s)
				{
					sweep.erase(it);
					flag = true;
					break;
				}
			}
			if (!flag)
				std::cout << __FILE__ << ":" << __LINE__
						  << " Error: cannot find segment " << s << " in sweep"
						  << std::endl;
			if (test)
			{
				if (segments[above->second].beg !=
					segments[below->second].beg)
				{
					std::pair<bool, Point> I =
						intersect(segments[below->second],
								  segments[above->second]);
					if (I.first)
					{
						intersections.push_back(I.second);
						intersect(below->second, above->second, I.second,
								  segments, sweep, events);
					}
				}
			}
		}
	}
}
