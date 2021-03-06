#include "CubeCube.h"



CubeCube::CubeCube()
{
}


CubeCube::~CubeCube()
{
}

CubeCube CubeCube::getObject()
{
	return *this;
}

void CubeCube::setObject(CubeCube theCube)
{
	*this = theCube;
}

int CubeCube::colortoi(char c)
{
	// subtract the the ascii value 0 from the characters 0 - 9
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

int CubeCube::getMaxFaces()
{
	return CubeCube::MAX_FACES;
}

bool CubeCube::isComplete()
{
	return MAX_FACES == currentNumFaces;
}

void CubeCube::rotateClockwiseFace(char f)
{
	deque<CubeColor> colors;
//	vector<CubeColor> colors;
	CubeFace tempFace;

	if (f == orientChar[0])  // Down face (D)
	{
		for (int i = 6; i < cube[_f[0]].getMaxColors(); i++)
		{
			colors.push_back(cube[_f[1]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));
			
			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[0]].rotateClockwise();

		solution += "D,";
	}
	else if (f == orientChar[1]) // Left face (L)
	{
		tempFace = cube[_f[4]];
		tempFace.rotateClockwise(2);
		for (int i = 0; i < cube[_f[0]].getMaxColors(); i+=3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(tempFace.getColors(i));

			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			tempFace.setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		tempFace.rotate180();
		cube[_f[4]] = tempFace;

		cube[_f[1]].rotateClockwise();
		solution += "L,";
	}
	else if (f == orientChar[2]) // Front face (F)
	{
		cube[_f[0]].rotateCounterClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateClockwise();
		for (int i = 0; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[1]].getColors(i));

			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[0]].rotateClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateCounterClockwise();

		cube[_f[2]].rotateClockwise();
		solution += "F,";
	}
	else if (f == orientChar[3]) // Right face (R)
	{
		cube[_f[4]].rotate180();
		for (int i = 2; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));

			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[4]].rotate180();

		cube[_f[3]].rotateClockwise();
		solution += "R,";
	}
	else if (f == orientChar[4]) // Back face (B)
	{
		cube[_f[0]].rotateCounterClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateClockwise();
		for (int i = 2; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[1]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));

			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[0]].rotateClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateCounterClockwise();

		solution += "B,";

		cube[_f[4]].rotateClockwise();
	}
	else if (f == orientChar[5]) // top face
	{
		for (int i = 0; i < cube[_f[0]].getMaxColors() - 6; i++)
		{
			colors.push_back(cube[_f[1]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));

			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
		}

		cube[_f[5]].rotateClockwise();
		solution += "U,";
	}
	CubeCube::totalMoves++;
}

void CubeCube::rotateCounterClockwiseFace(char f)
{
	deque<CubeColor> colors;
	//	vector<CubeColor> colors;
	CubeFace tempFace;

	if (f == orientChar[0])  // Down face (D)
	{
		for (int i = 6; i < cube[_f[0]].getMaxColors(); i++)
		{
			colors.push_back(cube[_f[1]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));

			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[0]].rotateCounterClockwise();

		solution += "D',";
	}
	else if (f == orientChar[1]) // Left face (L)
	{
		// rotate all adjacent sides
		//  +---+---+---+
		//  |   |   | X |
		//  +---+---+---+
		//  |   |   | X |
		//  +---+---+---+
		//  |   |   | X |
		//  +---+---+---+

		cube[_f[4]].rotate180();
		for (int i = 0; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));

			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[4]].rotate180();

		cube[_f[1]].rotateCounterClockwise();
		solution += "L',";
	}
	else if (f == orientChar[2]) // Front face (F)
	{
		// rotate all adjacent sides
		//  +---+---+---+
		//  | X |   |   |
		//  +---+---+---+
		//  | X |   |   |
		//  +---+---+---+
		//  | X |   |   |
		//  +---+---+---+

		cube[_f[0]].rotateCounterClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateClockwise();
		for (int i = 0; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[1]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));

			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[0]].rotateClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateCounterClockwise();

		cube[_f[2]].rotateCounterClockwise();
		solution += "F',";
	}
	else if (f == orientChar[3]) // Right face (R)
	{
		// rotate all adjacent sides
		//  +---+---+---+
		//  |   |   | X |
		//  +---+---+---+
		//  |   |   | X |
		//  +---+---+---+
		//  |   |   | X |
		//  +---+---+---+

		cube[_f[4]].rotate180();
		for (int i = 2; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));

			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[4]].rotate180();

		cube[_f[3]].rotateCounterClockwise();
		solution += "R',";
	}
	else if (f == orientChar[4]) // Back face (B)
	{
		// rotate all adjacent sides
		//  +---+---+---+
		//  | X | X | X |
		//  +---+---+---+
		//  |   |   |   |
		//  +---+---+---+
		//  |   |   |   |
		//  +---+---+---+

		cube[_f[0]].rotateCounterClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateClockwise();
		for (int i = 2; i < cube[_f[0]].getMaxColors(); i += 3)
		{
			colors.push_back(cube[_f[5]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));
			colors.push_back(cube[_f[0]].getColors(i));
			colors.push_back(cube[_f[1]].getColors(i));

			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[0]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[5]].setColor(colors.front(), i);
			colors.pop_front();
		}
		cube[_f[0]].rotateClockwise();
		cube[_f[1]].rotate180();
		cube[_f[5]].rotateCounterClockwise();

		cube[_f[4]].rotateCounterClockwise();
		solution += "B',";
	}
	else if (f == orientChar[5]) // top face
	{
		for (int i = 0; i < cube[_f[0]].getMaxColors() - 6; i++)
		{
			colors.push_back(cube[_f[1]].getColors(i));
			colors.push_back(cube[_f[2]].getColors(i));
			colors.push_back(cube[_f[3]].getColors(i));
			colors.push_back(cube[_f[4]].getColors(i));

			cube[_f[2]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[3]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[4]].setColor(colors.front(), i);
			colors.pop_front();
			cube[_f[1]].setColor(colors.front(), i);
			colors.pop_front();
		}

		cube[_f[5]].rotateCounterClockwise();
		solution += "U',";
	}
	CubeCube::totalMoves++;
}

void CubeCube::rotateFromFeed(string sMoves)
{
	stringstream ssMove(sMoves);
	vector<string> moves;
	string move;
	//	cout << "----------------------" << endl;
	//	cout << sMoves << endl;
	while (getline(ssMove, move, ','))
	{
		//		cout << move << " ";
		moves.push_back(move);

		if (move == "D")
			rotateClockwiseFace(orientChar.at(0));
		else if (move == "L")
			rotateClockwiseFace(orientChar.at(1));
		else if (move == "F")
			rotateClockwiseFace(orientChar.at(2));
		else if (move == "R")
			rotateClockwiseFace(orientChar.at(3));
		else if (move == "B")
			rotateClockwiseFace(orientChar.at(4));
		else if (move == "U")
			rotateClockwiseFace(orientChar.at(5));
		else if (move == "D'")
			rotateCounterClockwiseFace(orientChar.at(0));
		else if (move == "L'")
			rotateCounterClockwiseFace(orientChar.at(1));
		else if (move == "F'")
			rotateCounterClockwiseFace(orientChar.at(2));
		else if (move == "R'")
			rotateCounterClockwiseFace(orientChar.at(3));
		else if (move == "B'")
			rotateCounterClockwiseFace(orientChar.at(4));
		else if (move == "U'")
			rotateCounterClockwiseFace(orientChar.at(5));
	}
	//cout << endl;

}

string CubeCube::getSolution()
{
	return CubeCube::solution;
}
//string CubeCube::getSolution()
//{
//	stringstream ssMove(solution);
//	vector<string> moves;
//	string move;
//	string nextMove;
//	while (getline(ssMove, move, ','))
//	{
//		moves.push_back(move);
//	}
//
//	for (int i = 0; i < solution.size(); i++)
//	{
//		if (i != 0 && i != solution.size())
//		{
//			if (solution.at(i) == solution.at(i + 1))
//			{
//
//			}
//			
//		}
//	}
//
//	return CubeCube::solution;
//}


// This is a super poor way of handling this.
// But this is where I am at right now...
// TODO: redo the whole project but better.
CubeFace CubeCube::getRight(int i)
{
	// get the next right face on the 
	if (i >= 1 && i <= 4)
	{
		if (i == 4)
		{
			return CubeCube::cube[_f[1]];
		}
		else 
		{
			return CubeCube::cube[_f[i + 1]];
		}
	}
	else if (i > 4)
	{
		return CubeCube::getRight(i - 4);
	}
	else if (i < 1)
	{
		return CubeCube::getRight(i + 4);
	}
	else
	{
		; // Shouldn't get here
	}

}

// TODO: Same as getRight
CubeFace CubeCube::getLeft(int i)
{
	// get the next Left face on the 
	if (i >= 1 && i <= 4)
	{
		if (i == 1)
		{
			return CubeCube::cube[_f[4]];
		}
		else
		{
			return CubeCube::cube[_f[i - 1]];
		}
	}
	else if (i > 4)
	{
		return CubeCube::getLeft(i - 4);
	}
	else if (i < 1)
	{
		return CubeCube::getLeft(i + 4);
	}
	else
	{
		; // Shouldn't get here
	}

}

CubeFace CubeCube::getOpposite(int i)
{
	// get the next right face on the 
	if (i >= 1 && i <= 4)
	{
		if (i > 2)
		{
			return CubeCube::cube[_f[i - 2]];
		}
		else
		{
			return CubeCube::cube[_f[i + 2]];
		}
	}
	else if (i > 4)
	{
		return CubeCube::getRight(i - 4);
	}
	else if (i < 1)
	{
		return CubeCube::getRight(i + 4);
	}
	else
	{
		; // Shouldn't get here
	}
}
//CubeColor CubeCube::getAdjacentEdge(int current, int edge)
//{
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	if ()
//	//}
//
//	if (edge == )
//
//}

// Solve the bottom cross
void CubeCube::solveStage1()
{
	for (int i = 0 + 1; i < 4 + 1; i++)
	{
		// The four times that the piece is on the right face, but needs to be spun into position
		if (cube[_f[i]].getColors(1).getTypeChar() == orientChar.at(i) && 
			cube[_f[5]].getEdge(i, true).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (cube[_f[i]].getColors(5).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(3).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (cube[_f[i]].getColors(3).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(5).getTypeChar() == orientChar.at(0))
		{
			rotateCounterClockwiseFace(orientChar.at(i));
		}
		else if (cube[_f[i]].getColors(7).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getEdge(i).getTypeChar() == orientChar.at(0))
		{
			; // Do nothing, Already in the right place
		}
		// The four times that the piece is on the right face, but has twisted orientation
		else if (cube[_f[i]].getColors(1).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getEdge(i,true).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(5).getTypeChar() == orientChar.at(0) &&
			getRight(i).getColors(3).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (cube[_f[i]].getColors(3).getTypeChar() == orientChar.at(0) &&
			getLeft(i).getColors(5).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (cube[_f[i]].getColors(7).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getEdge(i).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		// The four cases where it's totally on the wrong face but in the "right" orientation
		else if (getOpposite(i).getColors(1).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getOppositeEdge(i, true).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getOpposite(i).getColors(5).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(3).getTypeChar() == orientChar.at(0))
		{
			rotateCounterClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		
		}
		else if (getOpposite(i).getColors(3).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(5).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getOpposite(i).getColors(7).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getOppositeEdge(i).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		// The four cases where it's on the wrong face and in the wrong orientation
		else if (getOpposite(i).getColors(1).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getOppositeEdge(i, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(5).getTypeChar() == orientChar.at(0) &&
			getLeft(i).getColors(3).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getOpposite(i).getColors(3).getTypeChar() == orientChar.at(0) &&
			getRight(i).getColors(5).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getOpposite(i).getColors(7).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getOppositeEdge(i).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));

		}
		// The four cases where the edge pieces are in the "middle" colom and have the "right" orientation
		else if (getRight(i).getColors(1).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getEdge(i + 1, true).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getLeft(i).getColors(1).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getEdge(i - 1, true).getTypeChar() == orientChar.at(0))
		{
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getRight(i).getColors(7).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getEdge(i + 1).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (getLeft(i).getColors(7).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getEdge(i - 1).getTypeChar() == orientChar.at(0))
		{
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(i));
		}
		// The four cases where the edge pieces are in the "middle" colom and have the wrong orientation
		else if (getRight(i).getColors(1).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getEdge(i + 1, true).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getLeft(i).getColors(1).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getEdge(i - 1, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(i));
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
		}
		else if (getRight(i).getColors(7).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getEdge(i + 1).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getLeft(i).getColors(7).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getEdge(i - 1).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(getLeft(i).getCenter().getTypeChar());
		}

		solution += " | ";
		CubeCube::totalSeq += 1;
	}
}

// Solve the bottom corners (technically appart of stage 1)
void CubeCube::solveStage2()
{
	for (int i = 0 + 1; i < 4 + 1; i++)
	{
		// The three times the corner cubie is in the right place but in the wrong orientation
		if (cube[_f[i]].getColors(8).getTypeChar() == orientChar.at(0) &&
			getRight(i).getColors(6).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getCorner(i, 2).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			// RU'R'URU'R
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(8).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getRight(i).getColors(6).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getCorner(i, 2).getTypeChar() == orientChar.at(i))
		{
			// RUR'U'RUR'
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(8).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(6).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[0]].getCorner(i, 2).getTypeChar() == orientChar.at(0))
		{
			; // Do nothing. Already in the right place
		}
		// The three times the cubie is directly above where it should go
		else if (cube[_f[i]].getColors(2).getTypeChar() == orientChar.at(0) &&
			getRight(i).getColors(0).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[5]].getCorner(i, 2, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(2).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(0).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getCorner(i, 2, true).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(2).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getRight(i).getColors(0).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getCorner(i, 2, true).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		// The three times the cubie is up and to the left of where it should go
		else if (cube[_f[i]].getColors(0).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getLeft(i).getColors(2).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getCorner(i, 1, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(0).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(2).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[5]].getCorner(i, 1, true).getTypeChar() == orientChar.at(0))
		{
			// U'RUUR'U'RUR'
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(0).getTypeChar() == orientChar.at(0) &&
			getLeft(i).getColors(2).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getCorner(i, 1, true).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		// The three times the cubie is up and to the right of where it should go
		else if (getOpposite(i).getColors(0).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(2).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[5]].getCorner(i + 1, 2, true).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(0).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getRight(i).getColors(2).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getCorner(i + 1, 2, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(0).getTypeChar() == orientChar.at(0) &&
			getRight(i).getColors(2).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getCorner(i + 1, 2, true).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		// The three times the cubie is on the top of the opposite side of the cube
		else if (getOpposite(i).getColors(2).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getLeft(i).getColors(0).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getCorner(i - 1, 1, true).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(2).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(0).getTypeChar() == orientChar.at(0) &&
			cube[_f[5]].getCorner(i - 1, 1, true).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(2).getTypeChar() == orientChar.at(0) &&
			getLeft(i).getColors(0).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[5]].getCorner(i - 1, 1, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		// The three times that the cubie is on the correct face but to the left of where it should be
		else if (cube[_f[i]].getColors(6).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getLeft(i).getColors(8).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getCorner(i, 1).getTypeChar() == orientChar.at(0))
		{
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (cube[_f[i]].getColors(6).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(8).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getCorner(i, 1).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(getLeft(i).getCenter().getTypeChar());

		}
		else if (cube[_f[i]].getColors(6).getTypeChar() == orientChar.at(0) &&
			getLeft(i).getColors(8).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[0]].getCorner(i, 1).getTypeChar() == orientChar.at(i))
		{
			cout << "Tick Tock!" << endl;
			rotateClockwiseFace(orientChar.at(i));
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(orientChar.at(i));
			rotateCounterClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
		}
		// The three times that the cubie is on the correct face but to the right of where it should be
		else if (getOpposite(i).getColors(6).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getRight(i).getColors(8).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getCorner(i + 1, 2).getTypeChar() == orientChar.at(0))
		{
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(6).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(8).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getCorner(i + 1, 2).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(6).getTypeChar() == orientChar.at(0) &&
			getRight(i).getColors(8).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[0]].getCorner(i + 1, 2).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		// The three times that the cubie is on the correct face but on the opposite side of where it should be
		else if (getOpposite(i).getColors(8).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(6).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[0]].getCorner(i - 1, 1).getTypeChar() == orientChar.at(0))
		{
			rotateCounterClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(8).getTypeChar() == orientChar.at(0) &&
			getLeft(i).getColors(6).getTypeChar() == orientChar.at(i) &&
			cube[_f[0]].getCorner(i - 1, 1).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateCounterClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
		}
		else if (getOpposite(i).getColors(8).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getLeft(i).getColors(6).getTypeChar() == orientChar.at(0) &&
			cube[_f[0]].getCorner(i - 1, 1).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getOpposite(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
		}
		solution += " | ";
		CubeCube::totalSeq += 1;
	}
}

// stage 3 algorithm helper right side
void CubeCube::edgeAlgRight(int i)
{
	if (i > 4)
		edgeAlgRight(i - 4);
	else if (i < 1)
		edgeAlgRight(i + 4);
	else
	{
		char f = orientChar.at(i); // front face
		char r = getRight(i).getCenter().getTypeChar(); // right face
		rotateClockwiseFace(r);
		rotateCounterClockwiseFace(orientChar.at(5));
		rotateCounterClockwiseFace(r);
		rotateCounterClockwiseFace(orientChar.at(5));
		rotateCounterClockwiseFace(f);
		rotateClockwiseFace(orientChar.at(5));
		rotateClockwiseFace(f);
	}
	return;
}

// stage 3 algorithm helper left side
void CubeCube::edgeAlgLeft(int i)
{
	if (i > 4)
		edgeAlgLeft(i - 4);
	else if (i < 1)
		edgeAlgLeft(i + 4);
	else
	{
		char f = orientChar.at(i); // front face
		char l = getLeft(i).getCenter().getTypeChar(); // left face
		rotateCounterClockwiseFace(l);
		rotateClockwiseFace(orientChar.at(5));
		rotateClockwiseFace(l);
		rotateClockwiseFace(orientChar.at(5));
		rotateClockwiseFace(f);
		rotateCounterClockwiseFace(orientChar.at(5));
		rotateCounterClockwiseFace(f);

	}
	return;
}

// Solve the middle layer corners
void CubeCube::solveStage3()
{
	for (int i = 0 + 1; i < 4 + 1; i++)
	{
		/*right side cubie*/
		//cout << "------------------------------------" << endl;
		//	cout << "SIDE: " << i << endl;
		//displayCube();
		//cout << "------------------------------------" << endl;

		// The three cases when the in the correct orientation but in the wrong place
		if (cube[_f[i]].getColors(3).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(5).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			// move cubie out
			rotateCounterClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getLeft(i).getCenter().getTypeChar());
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(orientChar.at(i));
			// move cubie in


			rotateCounterClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());

		}
		else if (cube[_f[i]].getColors(1).getTypeChar() == orientChar.at(i) &&
			cube[_f[5]].getEdge(i, true).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			// move cubie in
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(getRight(i).getCenter().getTypeChar());
			rotateCounterClockwiseFace(orientChar.at(5));
			rotateCounterClockwiseFace(orientChar.at(i));
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(i));
		}
		else if (cube[_f[i]].getColors(5).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(3).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			; // In the correct place. Do nothing.
		}
		// The three cases when in the wrong orientation and in the wrong place
		else if (cube[_f[i]].getColors(3).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getLeft(i).getColors(5).getTypeChar() == orientChar.at(i))
		{
			edgeAlgLeft(i);
			rotateCounterClockwiseFace(orientChar.at(5));
			edgeAlgRight(i);

		}
		else if (cube[_f[i]].getColors(1).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			cube[_f[5]].getEdge(i, true).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			edgeAlgLeft(i + 1);
		}
		else if (cube[_f[i]].getColors(5).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getRight(i).getColors(3).getTypeChar() == orientChar.at(i))
		{
			edgeAlgRight(i);
			rotateCounterClockwiseFace(orientChar.at(5));
			edgeAlgRight(i);

		}
		// The four cases where the edge cubie is in the middle layer
		else if (cube[_f[5]].getEdge(i - 1, true).getTypeChar() == orientChar.at(i) &&
			getLeft(i).getColors(1).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateClockwiseFace(orientChar.at(5));
			edgeAlgLeft(i + 1);
		}
		else if (cube[_f[5]].getEdge(i + 1, true).getTypeChar() == orientChar.at(i) &&
			getRight(i).getColors(1).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			rotateCounterClockwiseFace(orientChar.at(5));
			edgeAlgLeft(i + 1);
		}
		else if (cube[_f[5]].getEdge(i - 1, true).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getLeft(i).getColors(1).getTypeChar() == orientChar.at(i))
		{
			edgeAlgRight(i);
		}
		else if (cube[_f[5]].getEdge(i + 1, true).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getRight(i).getColors(1).getTypeChar() == orientChar.at(i))
		{
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			edgeAlgRight(i);
		}
		// The three cases where the edge cubie is on the opposite face in the wrong orientation
		else if (cube[_f[5]].getOppositeEdge(i, true).getTypeChar() == orientChar.at(i) &&
			getOpposite(i).getColors(1).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			edgeAlgLeft(i + 1);
		}
		else if (getLeft(i).getColors(3).getTypeChar() == orientChar.at(i) &&
			getOpposite(i).getColors(5).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			edgeAlgRight(i + 2);
			rotateClockwiseFace(orientChar.at(5));
			edgeAlgRight(i);
		}
		else if (getRight(i).getColors(5).getTypeChar() == orientChar.at(i) &&
			getOpposite(i).getColors(3).getTypeChar() == getRight(i).getCenter().getTypeChar())
		{
			edgeAlgRight(i + 1);
			rotateClockwiseFace(orientChar.at(5));
			edgeAlgLeft(i + 1);
		}
		// The three cases where the edge cubie is on the opposite face and in the "correct" orientation
		else if (cube[_f[5]].getOppositeEdge(i, true).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getOpposite(i).getColors(1).getTypeChar() == orientChar.at(i))
		{
			rotateCounterClockwiseFace(orientChar.at(5));
			edgeAlgRight(i);
		//	cout << "error here 1" << endl;
		//	displayCube();
		}
		else if (getLeft(i).getColors(3).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getOpposite(i).getColors(5).getTypeChar() == orientChar.at(i))
		{
			edgeAlgRight(i + 2);
			rotateClockwiseFace(orientChar.at(5));
			rotateClockwiseFace(orientChar.at(5));
			edgeAlgLeft(i + 1);
		}
		else if (getRight(i).getColors(5).getTypeChar() == getRight(i).getCenter().getTypeChar() &&
			getOpposite(i).getColors(3).getTypeChar() == orientChar.at(i))
		{
			edgeAlgRight(i + 1);
			edgeAlgRight(i);
		}

		solution += " | ";
		CubeCube::totalSeq += 1;
	}


}

string CubeCube::getUpColors()
{
	string upColorLocations;

	CubeFace temp = cube[_f[5]];
	for (int i = 0; i < temp.getMaxColors(); i++)
	{
		if (temp.getColors(i).getTypeChar() == orientChar.at(5))
		{
			upColorLocations += "1";
		}
		else
		{
			upColorLocations += "0";
		}
	}

	// loop throught middle faces
	for (int i = 1; i < 5; i++)
	{
		// loop through top layer of middle faces
		for (int j = 0; j < 3; j++)
		{
			if (cube[_f[i]].getColors(j).getTypeChar() == orientChar.at(5))
			{
				upColorLocations += "1";
			}
			else
			{
				upColorLocations += "0";
			}
		}
	}

	return upColorLocations;
}

vector<vector<string>> CubeCube::readPossibleCubeStates()
{
	ifstream infile("upFaceMoves.txt");

	string line;
	string segment;
	vector<vector<string>> data;
	while (getline(infile, line))
	{
		stringstream ssline(line);
		vector<string> item;

		while (getline(ssline, segment, '/'))
		{
			item.push_back(segment);
		}

		data.push_back(item);
	}
	infile.close();

	return data;
}

vector<string> CubeCube::readFile(string fileName)
{
	ifstream infile(fileName);

	string line;
	vector<string> data;
	while (getline(infile, line))
	{
		data.push_back(line);
	}
	infile.close();

	return data;
}

// checks to see if one face is solved... probably should be in CubeFace...
bool CubeCube::isFaceSolved(int index)
{
	char c = cube[_f[index]].getCenter().getTypeChar();

	bool isDiff = false;
	for (int i = 0; i < cube[_f[index]].getMaxColors(); i++)
	{
		if (cube[_f[index]].getColors(i).getTypeChar() != c)
		{
			isDiff = true;
		}
	}

	return !isDiff;
}

void CubeCube::solveStage4()
{
	// Using the Fridrich's 40 move method... Except I added all mirrors and alt orrientations,
	//  totalling 98 different top layer cube states.
	// Sources: 
    //  http://www.speedcubing.com/chris/3-orientations.html
	//  http://www.ai.univ-paris8.fr/~bh/cube/solutions_o1.html

	//cout << "Up Colors = " << getUpColors() << endl;

	vector<vector<string>> cubeStates = readPossibleCubeStates();


	//rotateClockwiseFace(orientChar.at(5));
	//cout << getSolution() << endl;
	//displayCube();

	while (!isFaceSolved(5))
	{
		for (int i = 0; i < cubeStates.size(); i++)
		{
			if (getUpColors() == cubeStates[i][0])
			{
				//cout << "Up Colors = " << getUpColors() << endl;
				//cout << "This state = " << cubeStates[i][0] << endl;
				rotateFromFeed(cubeStates[i][1]);
			}
		}
		rotateClockwiseFace(orientChar.at(5));
	}
	solution += " | ";
	CubeCube::totalSeq += 1;

}

bool CubeCube::isCubeSolved()
{
	bool isSolved = true;
	for (int i = 0; i < MAX_FACES; i++)
	{
		if (!isFaceSolved(i))
		{
			isSolved = false;
		}
	}
	return isSolved;
}

void CubeCube::solveStage5()
{
	//cout << "top complete" << endl;
	//displayCube();
	CubeCube tempSaveCube = this->getObject();

	vector<string> lastMoves = readFile("lastFaceMoves.txt");

	//rotateClockwiseFace('g');
	//cout << "check1" << endl;
	//displayCube();

	//this->setObject(tempSaveCube.getObject());
	//cout << "end check1" << endl;
	//displayCube();
	int k = 0;
	while (!isCubeSolved())
	{
		for (int i = 0; i < lastMoves.size(); i++)
		{
			//if (k == 2 && i == 11)
			//{
			//	cout << "first time" << endl;
			//	displayCube();
			//}
			rotateFromFeed(lastMoves[i]);
			//cout << "the move: " << lastMoves[i] << endl;
			if (i == 1)
			{
				//cout << "second time" << endl;
				//displayCube();
			}
			if (isCubeSolved())
			{
				return;
			}
			else 
			{
				for (int j = 0; j < 4; j++)
				{
					rotateClockwiseFace(orientChar.at(5));

					if (k == 2 && i == 11)
					{
						//cout << "alg num: " << k << " " << i << " " << j << endl;
						//displayCube();
//						return;
					}

					if (isCubeSolved())
					{
						return;
					}
				}

				// start over check
				this->setObject(tempSaveCube.getObject());
				for (int i = 0; i < k + 1; i++)
				{
					//cout << "1rotate " << i << " times" << endl;
					rotateClockwiseFace(orientChar.at(5));
				}
			}
			if (k == 2 && i == 11)
			{
				//cout << "alg num: " << i << endl;
				//displayCube();
				//return;
			}

		}
		// none of the moves worked rotate and start over
		for (int i = 0; i < k + 1; i++)
		{
			//cout << "2rotate " << i << " times" << endl;
			rotateClockwiseFace(orientChar.at(5));
		}
		k++;
		//cout << k++ << endl;
	}
	solution += " | ";
	CubeCube::totalSeq += 1;

	return;
}

int CubeCube::getTotalMoves()
{
	return CubeCube::totalMoves;
}

int CubeCube::getTotalSeq()
{
	return CubeCube::totalSeq;
}

void CubeCube::solveCube()
{
	solveStage1();
	solveStage2();
	solveStage3();
	solveStage4();
	solveStage5();
	//cout << "Total Moves = " << CubeCube::totalMoves << endl;
	//cout << "Total Sequences = " << CubeCube::totalSeq << endl;
	//cout << getSolution() << endl;
}



void CubeCube::saveCube()
{
	ofstream outSaveCube(CubeCube::saveFileName);
	
	for (int i = 0; i < MAX_FACES; i++)
	{
		for (int j = 0; j < cube[_f[i]].getMaxColors(); j++)
		{
			if (j == cube[_f[i]].getMaxColors() - 1)
				outSaveCube << cube[_f[i]].getColors(j).getType();
			else
				outSaveCube << cube[_f[i]].getColors(j).getType() << ",";
		}
		outSaveCube << endl;
	}
	outSaveCube.close();
	return;
}

void CubeCube::loadCube()
{
	CubeCube::isLoading = true;
	vector<vector<string>> cubeData;
	string line;
	string color;

	// read the cube save file
	ifstream inloadCube(CubeCube::saveFileName);
	while (getline(inloadCube, line))
	{
		stringstream ssLine(line);
		vector<string> lineData;
		while (getline(ssLine, color, ','))
		{
			lineData.push_back(color);
		}

		cubeData.push_back(lineData);
	}
	inloadCube.close();

	// Create the cube
	for (int i = 0; i < cubeData.size(); i++)
	{
		CubeFace theFace;
		vector<CubeColor> faceColor;
		for (int j = 0; j < cubeData[i].size(); j++)
		{
			// Set each face Color
			CubeColor color(cubeData[i][j], 1);
			faceColor.push_back(color);
		}
		// Push each face color to the Face
		theFace.setColors(faceColor);
		// Push each face to the Cube
		CubeCube::setFace(theFace);
	}
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
	//cout << orientChar[0] << endl;
	//cout << color << endl;
	//cout << _f[0] << endl;
	//cout << _f[1] << endl;
	//cout << _f[2] << endl;
	//cout << _f[3] << endl;
	//cout << _f[4] << endl;
	//cout << _f[5] << endl;
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
			if (currentNumFaces == 2 && !isLoading)
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
			if (currentNumFaces == 2 && !isLoading)
				CubeCube::cube[_f[0]].rotateClockwise(1);

			CubeCube::cube[_f[3]] = theFace;
		}

	}
	else if (color == orientChar[4]) // back color face
	{
		if (CubeCube::cube[_f[4]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			// rotate face clockwise 2 times
			if (currentNumFaces == 2 && !isLoading)
				CubeCube::cube[_f[0]].rotateClockwise(2);
			
			CubeCube::cube[_f[4]] = theFace;
		}

	}
	else if (color == orientChar[5]) // top color face
	{
		if (CubeCube::cube[_f[5]].getCenter().getTypeChar() == '!')  // Once set colors shouldn't change
		{
			if (lastSetFace == orientChar[1] && !isLoading)
				theFace.rotateClockwise(1);
			else if (lastSetFace == orientChar[2] && !isLoading)
				; // do nothing already has correct orientation
			else if (lastSetFace == orientChar[3] && !isLoading)
				theFace.rotateClockwise(3);
			else if (lastSetFace == orientChar[4] && !isLoading)
				theFace.rotateClockwise(2);

			CubeCube::cube[_f[5]] = theFace;
		}
	}

	//throw new string("Error invalid color");

	//}
	lastSetFace = color;

	//orientFaces();
}

void CubeCube::displayRules()
{
	cout << " The Faces: " << endl;
	cout << "  Down  (D) = " << cube[_f[0]].getCenter().getType() << endl;
	cout << "  Left  (L) = " << cube[_f[1]].getCenter().getType() << endl;
	cout << "  Front (F) = " << cube[_f[2]].getCenter().getType() << endl;
	cout << "  Right (R) = " << cube[_f[3]].getCenter().getType() << endl;
	cout << "  Back  (B) = " << cube[_f[4]].getCenter().getType() << endl;
	cout << "  Up    (U) = " << cube[_f[5]].getCenter().getType() << endl;
	cout << endl;
	cout << "  Letters marked with a prime like R' is a counter clockwise turn of that face otherwise" << endl;
	cout << "  all turns are clockwise." << endl;
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
