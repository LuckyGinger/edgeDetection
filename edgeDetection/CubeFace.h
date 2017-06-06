#pragma once
#include "CubeColor.h"


class CubeFace
{
public:
	CubeFace();
	~CubeFace();

	void setColors(vector<CubeColor> color, Mat image);

	void displayFace();

private:
	string color;

	static const int MAX_COLORS = 9;
	CubeColor face[MAX_COLORS];

};

