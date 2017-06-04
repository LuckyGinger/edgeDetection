#pragma once
#include "CubeColor.h"

class CubeFace
{
public:
	CubeFace();
	~CubeFace();
private:
	static const int MAX_COLORS = 9;
	CubeColor face[MAX_COLORS];

};

