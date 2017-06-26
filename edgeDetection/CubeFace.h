#pragma once
#include "CubeColor.h"


class CubeFace
{
public:
	CubeFace();
	~CubeFace();

	void setColors(vector<CubeColor> color, Mat image);
	void setColors(vector<CubeColor> color);

	CubeColor getColors(int loc);
	CubeColor getCenter();

	void rotateClockwise(int num);

	void displayFace();

	int getMaxColors();

private:
	string color;

	static const int MAX_COLORS = 9;
	CubeColor face[MAX_COLORS];

};

