#pragma once
#include "CubeFace.h"

class CubeCube
{
public:
	CubeCube();
	~CubeCube();
private:
	static const int MAX_FACES = 6;
	CubeFace cube[MAX_FACES];


	
};

