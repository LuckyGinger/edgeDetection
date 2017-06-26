#pragma once
#include <fstream>
#include <string>
#include <vector>


class CubeStore
{
public:
	CubeStore();
	~CubeStore();

	void saveCube();
	void loadCube();
};

