#include "CubeCube.h"



CubeCube::CubeCube()
{ 
}


CubeCube::~CubeCube()
{
}

void CubeCube::setFace(CubeFace theFace)
{
	int center = 4;
	CubeColor centerColor = theFace.getColors(center);
	char color = centerColor.getType().at(0);


	// get the center color for the face
	if (color == 'r')
	{
		CubeCube::cube[r] = theFace;

	}
	else if (color == 'g')
	{
		CubeCube::cube[g] = theFace;

	}
	else if (color == 'b')
	{
		CubeCube::cube[b] = theFace;

	}
	else if (color == 'w')
	{
		CubeCube::cube[w] = theFace;

	}
	else if (color == 'o')
	{
		CubeCube::cube[o] = theFace;

	}
	else if (color == 'y')
	{
		CubeCube::cube[y] = theFace;
	}

	//throw new string("Error invalid color");

	//}
}


void CubeCube::displayCube()
{
	string hrz = " +---+---+---+";

	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[b].getColors(0).getType().at(0) << " | " << cube[b].getColors(1).getType().at(0) << " | " << cube[b].getColors(2).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[b].getColors(3).getType().at(0) << " | " << cube[b].getColors(4).getType().at(0) << " | " << cube[b].getColors(5).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[b].getColors(6).getType().at(0) << " | " << cube[b].getColors(7).getType().at(0) << " | " << cube[b].getColors(8).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;

	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;

	// display | o | w | r | y |
	cout << " | " << cube[o].getColors(0).getType().at(0) << " | " << cube[o].getColors(1).getType().at(0) << " | " << cube[o].getColors(2).getType().at(0) << " |";
	cout << " | " << cube[w].getColors(0).getType().at(0) << " | " << cube[w].getColors(1).getType().at(0) << " | " << cube[w].getColors(2).getType().at(0) << " |";
	cout << " | " << cube[r].getColors(0).getType().at(0) << " | " << cube[r].getColors(1).getType().at(0) << " | " << cube[r].getColors(2).getType().at(0) << " |";
	cout << " | " << cube[y].getColors(0).getType().at(0) << " | " << cube[y].getColors(1).getType().at(0) << " | " << cube[y].getColors(2).getType().at(0) << " |" << endl;
	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;
	cout << " | " << cube[o].getColors(3).getType().at(0) << " | " << cube[o].getColors(4).getType().at(0) << " | " << cube[o].getColors(5).getType().at(0) << " |";
	cout << " | " << cube[w].getColors(3).getType().at(0) << " | " << cube[w].getColors(4).getType().at(0) << " | " << cube[w].getColors(5).getType().at(0) << " |";
	cout << " | " << cube[r].getColors(3).getType().at(0) << " | " << cube[r].getColors(4).getType().at(0) << " | " << cube[r].getColors(5).getType().at(0) << " |";
	cout << " | " << cube[y].getColors(3).getType().at(0) << " | " << cube[y].getColors(4).getType().at(0) << " | " << cube[y].getColors(5).getType().at(0) << " |" << endl;
	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;
	cout << " | " << cube[o].getColors(6).getType().at(0) << " | " << cube[o].getColors(7).getType().at(0) << " | " << cube[o].getColors(8).getType().at(0) << " |";
	cout << " | " << cube[w].getColors(6).getType().at(0) << " | " << cube[w].getColors(7).getType().at(0) << " | " << cube[w].getColors(8).getType().at(0) << " |";
	cout << " | " << cube[r].getColors(6).getType().at(0) << " | " << cube[r].getColors(7).getType().at(0) << " | " << cube[r].getColors(8).getType().at(0) << " |";
	cout << " | " << cube[y].getColors(6).getType().at(0) << " | " << cube[y].getColors(7).getType().at(0) << " | " << cube[y].getColors(8).getType().at(0) << " |" << endl;
	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;

	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[g].getColors(0).getType().at(0) << " | " << cube[g].getColors(1).getType().at(0) << " | " << cube[g].getColors(2).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[g].getColors(3).getType().at(0) << " | " << cube[g].getColors(4).getType().at(0) << " | " << cube[g].getColors(5).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[g].getColors(6).getType().at(0) << " | " << cube[g].getColors(7).getType().at(0) << " | " << cube[g].getColors(8).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;

	cout << endl;
}
