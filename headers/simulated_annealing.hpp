#pragma once

#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP 

#include "../headers/cgalConfig.hpp"

namespace simulated_annealing{
	Polygon_2* simulatedAnnealing(std::vector<Point_2> &points, char* annealing, bool max, int L, double &initialArea, double &finalArea);
	//Polygon_2* simulatedAnnealingWithSubdivision(std::vector<Point_2> &points, bool max);

	void localTransitionStep(Polygon_2 &polygon, double &changeOfPolygonArea, int &indexOfFirstPoint);
	void globalTransitionStep(Polygon_2 &polygon, double &changeOfPolygonArea, int &indexOfPoint, int &indexOfNewPlace);

	void swapTwoPoints(Polygon_2 &polygon, int indexOfFirstPoint);
	void changePositionOfPoint(Polygon_2 &polygon, int &indexOfPoint, int &indexOfNewPosition);
	int triangleOrientation(Point_2 &a, Point_2 &b, Point_2 &c);

	void getConvexHullPolygonFromPoints(const std::vector<Point_2> &points, int begin, int end, Polygon_2 &convexHullPolygon);
	//void getLowerHullPolygonFromPoints(const std::vector<Point_2> &points, int begin, int end, Polygon_2 &convexHullPolygon);

	int maxCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
	int maxCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
	int minCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
	int minCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
} 

#endif