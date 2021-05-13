#ifndef MYMATH_H_
#define MYMATH_H_

#include <cmath>

class MyMath
{
public:
	static const float Sqrt2;
	static const float PI;
	static const float Deg2Rad;

	static bool CircleCircleIntersection(
		float x1, float y1, float radius1,
		float x2, float y2, float radius2);
	static float PointToPointAngle(
		float fromX, float fromY, float toX, float toY);

};

#endif // !MYMATH_H_

