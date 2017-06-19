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
	string temp;
	while (getline(infile, line))
	{
		if (line[0] == c)
		{
			temp = line;
			CubeCube::orient = line.substr(2, 7); // set the orient string
			CubeCube::orientChar = temp.substr(9, 15);
			cout << orient << endl;
			cout << orientChar << endl;
		}
	}
	infile.close();

	// Because I have no idea how else to do this...
	// Converts strings to int
	// string "31245" to int of one number totalling 6 numbers
	_f[0] = orient.c_str()[0] - '0';
	_f[1] = orient.c_str()[1] - '0';
	_f[2] = orient.c_str()[2] - '0';
	_f[3] = orient.c_str()[3] - '0';
	_f[4] = orient.c_str()[4] - '0';
	_f[5] = orient.c_str()[5] - '0';

}

void CubeCube::orientFaces()
{

}

int colortoi(char c)
{
	switch (c)
	{
	case 'r':
		return 0;
	case 'g':
		return 1;
	case 'b':
		return 2;
	case 'w':
		return 3;
	case 'o':
		return 4;
	case 'y':
		return 5;
	}

	return -1; // bad color input
}

void CubeCube::setFace(CubeFace theFace)
{

	char color = (char)theFace.getCenter().getTypeChar();

	// convert the color
//	int c = colortoi(color)

	if (!bottomFace)
	{
		bottomFace = color;
		setOrient(color);
	}


	// get the center color for the face
	cout << orientChar[0] << endl;
	cout << color << endl;
	cout << _f[0] << endl;
	cout << _f[1] << endl;
	cout << _f[2] << endl;
	cout << _f[3] << endl;
	cout << _f[4] << endl;
	cout << _f[5] << endl;
	if (color == orientChar[0])
	{
		if (CubeCube::cube[_f[0]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[0]] = theFace;
		}

	}
	else if (color == orientChar[1])
	{
		if (CubeCube::cube[_f[1]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[1]] = theFace;
		}
	}
	else if (color == orientChar[2])
	{
		if (CubeCube::cube[_f[2]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[2]] = theFace;
		}

	}
	else if (color == orientChar[3])
	{
		if (CubeCube::cube[_f[3]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[3]] = theFace;
		}

	}
	else if (color == orientChar[4])
	{
		if (CubeCube::cube[_f[4]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[4]] = theFace;
		}

	}
	else if (color == orientChar[5])
	{
		if (CubeCube::cube[_f[5]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[5]] = theFace;
		}
	}

	//throw new string("Error invalid color");

	//}

	orientFaces();
}


void CubeCube::displayCube()
{
	cout << "Bottom Face: " << bottomFace << " " << orient << " " << orientChar << endl;
	string hrz = " +---+---+---+";

	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[_f[5]].getColors(0).getType().at(0) << " | " << cube[_f[5]].getColors(1).getType().at(0) << " | " << cube[_f[5]].getColors(2).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[_f[5]].getColors(3).getType().at(0) << " | " << cube[_f[5]].getColors(4).getType().at(0) << " | " << cube[_f[5]].getColors(5).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[_f[5]].getColors(6).getType().at(0) << " | " << cube[_f[5]].getColors(7).getType().at(0) << " | " << cube[_f[5]].getColors(8).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;

	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;

	// display | o | w | r | y |
	cout << " | " << cube[_f[1]].getColors(0).getType().at(0) << " | " << cube[_f[1]].getColors(1).getType().at(0) << " | " << cube[_f[1]].getColors(2).getType().at(0) << " |";
	cout << " | " << cube[_f[2]].getColors(0).getType().at(0) << " | " << cube[_f[2]].getColors(1).getType().at(0) << " | " << cube[_f[2]].getColors(2).getType().at(0) << " |";
	cout << " | " << cube[_f[3]].getColors(0).getType().at(0) << " | " << cube[_f[3]].getColors(1).getType().at(0) << " | " << cube[_f[3]].getColors(2).getType().at(0) << " |";
	cout << " | " << cube[_f[4]].getColors(0).getType().at(0) << " | " << cube[_f[4]].getColors(1).getType().at(0) << " | " << cube[_f[4]].getColors(2).getType().at(0) << " |" << endl;
	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;
	cout << " | " << cube[_f[1]].getColors(3).getType().at(0) << " | " << cube[_f[1]].getColors(4).getType().at(0) << " | " << cube[_f[1]].getColors(5).getType().at(0) << " |";
	cout << " | " << cube[_f[2]].getColors(3).getType().at(0) << " | " << cube[_f[2]].getColors(4).getType().at(0) << " | " << cube[_f[2]].getColors(5).getType().at(0) << " |";
	cout << " | " << cube[_f[3]].getColors(3).getType().at(0) << " | " << cube[_f[3]].getColors(4).getType().at(0) << " | " << cube[_f[3]].getColors(5).getType().at(0) << " |";
	cout << " | " << cube[_f[4]].getColors(3).getType().at(0) << " | " << cube[_f[4]].getColors(4).getType().at(0) << " | " << cube[_f[4]].getColors(5).getType().at(0) << " |" << endl;
	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;
	cout << " | " << cube[_f[1]].getColors(6).getType().at(0) << " | " << cube[_f[1]].getColors(7).getType().at(0) << " | " << cube[_f[1]].getColors(8).getType().at(0) << " |";
	cout << " | " << cube[_f[2]].getColors(6).getType().at(0) << " | " << cube[_f[2]].getColors(7).getType().at(0) << " | " << cube[_f[2]].getColors(8).getType().at(0) << " |";
	cout << " | " << cube[_f[3]].getColors(6).getType().at(0) << " | " << cube[_f[3]].getColors(7).getType().at(0) << " | " << cube[_f[3]].getColors(8).getType().at(0) << " |";
	cout << " | " << cube[_f[4]].getColors(6).getType().at(0) << " | " << cube[_f[4]].getColors(7).getType().at(0) << " | " << cube[_f[4]].getColors(8).getType().at(0) << " |" << endl;
	for (int i = 0; i < 4; i++)
		cout << hrz;
	cout << endl;

	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[_f[0]].getColors(0).getType().at(0) << " | " << cube[_f[0]].getColors(1).getType().at(0) << " | " << cube[_f[0]].getColors(2).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[_f[0]].getColors(3).getType().at(0) << " | " << cube[_f[0]].getColors(4).getType().at(0) << " | " << cube[_f[0]].getColors(5).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;
	cout << setw(17) << " | " << cube[_f[0]].getColors(6).getType().at(0) << " | " << cube[_f[0]].getColors(7).getType().at(0) << " | " << cube[_f[0]].getColors(8).getType().at(0) << " | " << endl;
	cout << setw(28) << hrz << endl;

	cout << endl;
}
