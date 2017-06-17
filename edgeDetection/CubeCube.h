#pragma once
#include "CubeFace.h"
#include <sstream>
#include <string>
#include <fstream>


class CubeCube
{
public:
	CubeCube();
	~CubeCube();

	void setFace(CubeFace theFace);
	void displayCube();

private:
	static const int MAX_FACES = 6;
	CubeFace cube[MAX_FACES];

	char bottomFace; 
	string orient;

	int r = 0;
	int g = 1;
	int b = 2;
	int w = 3;
	int o = 4;
	int y = 5;


	void orientFaces();
	void setOrient(char color);  // take the bottom color

};

