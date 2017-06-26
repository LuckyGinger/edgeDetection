#pragma once
#include "CubeFace.h"
#include "CubeStore.h"
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>

class CubeCube
{
public:
	CubeCube();
	~CubeCube();

	void setFace(CubeFace theFace);
	void displayCube();
	
	int getNumSetFaces();  // TODO: implement this without counter
	int getMaxFaces();
	bool isComplete();

	void saveCube();

	void loadCube();

private:
	static const int MAX_FACES = 6;
	CubeFace cube[MAX_FACES];

	int currentNumFaces = 0;

	char bottomFace; 
	char lastSetFace;
	string orient;
	string orientChar;
	bool isLoading = false;


	int _f[MAX_FACES] = { 0,0,0,0,0,0 };

	int colortoi(char c);

	string saveFileName = "cubeSave.txt";

	void orientFaces();
	void setOrient(char color);  // take the bottom color

};

