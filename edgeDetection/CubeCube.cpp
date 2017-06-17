#include "CubeCube.h"



CubeCube::CubeCube()
{
}


CubeCube::~CubeCube()
{
}

void CubeCube::setOrient(char c)
{
	// Read from orient file
	ifstream infile("colordata.txt");

	string line;
	while (getline(infile, line))
	{
		if (line[0] == c)
		{
			CubeCube::orient = line; // set the orient string
		}
	}
}

void CubeCube::orientFaces()
{

}

void CubeCube::setFace(CubeFace theFace)
{

	char color = theFace.getCenter().getTypeChar();

	if (!bottomFace)
	{
		bottomFace = color;
		setOrient(color);
	}


	// get the center color for the face
	if (color == 'r')
	{
		if (CubeCube::cube[r].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[r] = theFace;
		}

	}
	else if (color == 'g')
	{
		if (CubeCube::cube[g].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[g] = theFace;
		}
	}
	else if (color == 'b')
	{
		if (CubeCube::cube[b].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[b] = theFace;
		}

	}
	else if (color == 'w')
	{
		if (CubeCube::cube[w].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[w] = theFace;
		}

	}
	else if (color == 'o')
	{
		if (CubeCube::cube[o].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[o] = theFace;
		}

	}
	else if (color == 'y')
	{
		if (CubeCube::cube[y].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[y] = theFace;
		}
	}

	//throw new string("Error invalid color");

	//}

	orientFaces();
}


void CubeCube::displayCube()
{
	cout << "Bottom Face: " << bottomFace << " " << orient << endl;
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
