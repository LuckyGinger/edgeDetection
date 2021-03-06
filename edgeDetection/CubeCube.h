#pragma once
#include "CubeFace.h"
#include "CubeStore.h"
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <deque>

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

	void solveCube();
	string getSolution();

	int getTotalMoves();
	int getTotalSeq();

	void displayRules();

private:
	static const int MAX_FACES = 6;
	CubeFace cube[MAX_FACES];

	int currentNumFaces = 0;

	char bottomFace; 
	char lastSetFace;
	string orient;
	string orientChar;
	bool isLoading = false;

	int totalMoves = 0;
	int totalSeq = 0;
	string solution = "";

	// Actuall location of face on cube array in int
	// _f[0] - Bottom
	// _f[1] - Left
	// _f[2] - Front
	// _f[3] - Right
	// _f[4] - Back
	// _f[5] - Top
	int _f[MAX_FACES] = { 0,0,0,0,0,0 };

	int colortoi(char c);

	string saveFileName = "cubeSave.txt";



	void orientFaces();
	void setOrient(char color);  // take the bottom color

	void rotateClockwiseFace(char f);
	void rotateCounterClockwiseFace(char f);

	void rotateFromFeed(string sMoves);

	CubeFace getRight(int i);
	CubeFace getLeft(int i);
	CubeFace getOpposite(int i);

	//CubeColor getAdjacentEdge(int current, int edge);

	void edgeAlgRight(int i);
	void edgeAlgLeft(int i);

	string getUpColors();
	vector<vector<string>> readPossibleCubeStates();
	vector<string> readFile(string fileName);
	bool isFaceSolved(int i);
	bool isCubeSolved();

	CubeCube getObject();
	void setObject(CubeCube theCube);

	void solveStage1();
	void solveStage2();
	void solveStage3();
	void solveStage4();
	void solveStage5();
};

