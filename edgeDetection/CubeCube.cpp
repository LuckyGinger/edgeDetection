#include "CubeCube.h"



CubeCube::CubeCube()
{
}


CubeCube::~CubeCube()
{
}

int CubeCube::colortoi(char c)
{
	// subtract the the ascii value 0 from the characters 1 - 9
	if (c - '0' > -1 && c - '0' < 10)
		return c - '0';
	else
		return -1;
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

	// Converts strings to int
	// string "31245" to int of one number totalling 6 numbers
	for (int i = 0; i < MAX_FACES; i++)
		_f[i] = colortoi(orient.c_str()[i]);

}

void CubeCube::orientFaces()
{
	bool isEdges = false;
	string line1;
	string line2;
	string line3;

	ifstream infile("pieces.txt");

	while (getline(infile, line1))
	{
		cout << line1 << endl;
		
		if (!isEdges)  // is Corners
		{
			if (line1 == "*")
				isEdges = true;
			else
			{
				getline(infile, line2);
				getline(infile, line3);
				// compare peices



			}

		}
		else  // is edges
		{

		}

		cout << line2 << endl;
		cout << line3 << endl;

		//if (line[0] == c)
		//{
		//	temp = line;
		//	CubeCube::orient = line.substr(2, 7); // set the orient string
		//	CubeCube::orientChar = temp.substr(9, 15);
		//	cout << orient << endl;
		//	cout << orientChar << endl;
		//}
	}
	infile.close();


}

int CubeCube::getNumSetFaces() 
{
	return CubeCube::currentNumFaces;
}


void CubeCube::setFace(CubeFace theFace)
{
	CubeCube::currentNumFaces++;

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
	if (color == orientChar[0])  // bottom color face
	{
		if (CubeCube::cube[_f[0]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			CubeCube::cube[_f[0]] = theFace;
		}

	}
	else if (color == orientChar[1]) // left color face
	{
		if (CubeCube::cube[_f[1]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			// rotate face counter clockwise (clockwise 3 times) // TODO: implement counter clockwise
			if (currentNumFaces == 2)
				CubeCube::cube[_f[0]].rotateClockwise(3);

			CubeCube::cube[_f[1]] = theFace;
		}
	}
	else if (color == orientChar[2]) // middle color face
	{
		if (CubeCube::cube[_f[2]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			// no need to rotate bottom face
			// already has correct orientation

			CubeCube::cube[_f[2]] = theFace;
		}

	}
	else if (color == orientChar[3]) // right color face
	{
		if (CubeCube::cube[_f[3]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			// rotate face clockwise 1 time
			if (currentNumFaces == 2)
				CubeCube::cube[_f[0]].rotateClockwise(1);

			CubeCube::cube[_f[3]] = theFace;
		}

	}
	else if (color == orientChar[4]) // back color face
	{
		if (CubeCube::cube[_f[4]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			// rotate face clockwise 2 times
			if (currentNumFaces == 2)
				CubeCube::cube[_f[0]].rotateClockwise(2);
			
			CubeCube::cube[_f[4]] = theFace;
		}

	}
	else if (color == orientChar[5]) // top color face
	{
		if (CubeCube::cube[_f[5]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			if (lastSetFace == orientChar[1])
				theFace.rotateClockwise(1);
			else if (lastSetFace == orientChar[2])
				; // do nothing already has correct orientation
			else if (lastSetFace == orientChar[3])
				theFace.rotateClockwise(3);
			else if (lastSetFace == orientChar[4])
				theFace.rotateClockwise(2);

			CubeCube::cube[_f[5]] = theFace;
		}
	}

	//throw new string("Error invalid color");

	//}
	lastSetFace = color;

	//orientFaces();
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
