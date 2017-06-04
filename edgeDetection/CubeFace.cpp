#include "CubeFace.h"



CubeFace::CubeFace()
{
}


CubeFace::~CubeFace()
{
	delete[] CubeFace::face;
}
