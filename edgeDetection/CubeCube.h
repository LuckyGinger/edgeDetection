#pragma once
#include "CubeFace.h"
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>

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
	string orientChar;

	int _f[MAX_FACES] = { 0,0,0,0,0,0 };

	int colortoi(char c);

	void orientFaces();
	void setOrient(char color);  // take the bottom color

};

