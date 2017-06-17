#pragma once
#include "CubeColor.h"


class CubeFace
{
public:
	CubeFace();
	~CubeFace();

	void setColors(vector<CubeColor> color, Mat image);

	CubeColor getColors(int loc);
	CubeColor getCenter();

	void rotateClockwise(int num);

	void displayFace();

private:
	string color;

	static const int MAX_COLORS = 9;
	CubeColor face[MAX_COLORS];

};

