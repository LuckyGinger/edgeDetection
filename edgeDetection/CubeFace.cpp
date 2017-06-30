#include "CubeFace.h"



CubeFace::CubeFace()
{
}


CubeFace::~CubeFace()
{
	//delete[] face;
}

int CubeFace::getMaxColors()
{
	return MAX_COLORS;
}

void CubeFace::rotate180()
{
	rotateClockwise(2);
}

void CubeFace::rotateCounterClockwise(int num)
{
	CubeColor temp[MAX_COLORS];

	for (int i = 0; i < num; i++)
	{
		// Top Left Color
		temp[6] = face[0];
		// Top Middle Color
		temp[3] = face[1];
		// Top Right Color
		temp[0] = face[2];
		// Center Left Color
		temp[7] = face[3];
		// Center Middle Color (stays the same)
		temp[4] = face[4];
		// Center Right Color
		temp[1] = face[5];
		// Bottom Left Color
		temp[8] = face[6];
		// Bottom Middle Color
		temp[5] = face[7];
		// Bottom Right Color
		temp[2] = face[8];
		for (int i = 0; i < MAX_COLORS; i++)
		{
			face[i] = temp[i];
		}
	}
}

void CubeFace::rotateClockwise(int num)
{
	CubeColor temp[MAX_COLORS];

	for (int i = 0; i < num; i++)
	{
		// Top Left Color
		temp[0] = face[6];
		// Top Middle Color
		temp[1] = face[3];
		// Top Right Color
		temp[2] = face[0];
		// Center Left Color
		temp[3] = face[7];
		// Center Middle Color (stays the same)
 		temp[4] = face[4];
		// Center Right Color
		temp[5] = face[1];
		// Bottom Left Color
		temp[6] = face[8];
		// Bottom Middle Color
		temp[7] = face[5];
		// Bottom Right Color
		temp[8] = face[2];
		for (int i = 0; i < MAX_COLORS; i++)
		{
			face[i] = temp[i];
		}
	}

	return;
}

// Mostly used for top and bottom faces
CubeColor CubeFace::getEdge(int loc, bool isTop)
{
	if (loc == 1)
	{
		return CubeFace::face[3];
	}
	else if (loc == 2 && isTop)
	{
		return CubeFace::face[7];
	}
	else if (loc == 2 && !isTop)
	{
		return CubeFace::face[1];
	}
	else if (loc == 3)
	{
		return CubeFace::face[5];
	}
	else if (loc == 4 && isTop)
	{
		return CubeFace::face[1];
	}
	else if (loc == 4 && !isTop)
	{
		return CubeFace::face[7];
	}
	else if (loc >= 5)
	{
		// if loc too large just sub 4 from loc and getEdge again
		return CubeFace::getEdge(loc - 4, isTop);
	}
	else if (loc <= 0)
	{
		// if loc too small just add 4 from loc and getEdge again
		return CubeFace::getEdge(loc + 4, isTop);
	}
	else
	{
		; // We shouldn't ever get here
	}
}

CubeColor CubeFace::getOppositeEdge(int loc, bool isTop)
{
	if (loc == 1)
	{
		return CubeFace::face[5];
	}
	else if (loc == 2 && isTop)
	{
		return CubeFace::face[1];
	}
	else if (loc == 2 && !isTop)
	{
		return CubeFace::face[7];
	}
	else if (loc == 3)
	{
		return CubeFace::face[3];
	}
	else if (loc == 4 && isTop)
	{
		return CubeFace::face[7];
	}
	else if (loc == 4 && !isTop)
	{
		return CubeFace::face[1];
	}
	else if (loc >= 5)
	{
		// if loc too large just sub 4 from loc and getEdge again
		return CubeFace::getOppositeEdge(loc - 4, isTop);
	}
	else if (loc <= 0)
	{
		// if loc too small just add 4 from loc and getEdge again
		return CubeFace::getOppositeEdge(loc + 4, isTop);
	}
	else
	{
		; // We shouldn't ever get here
	}
}

CubeColor CubeFace::getCorner(int theFace, int loc, bool isTop)
{
	// TODO: account for the top face
	if (theFace == 1)
	{
		if (loc == 1)
		{
			return isTop ? CubeFace::face[0] : CubeFace::face[6];
		}
		else if (loc == 2)
		{
			return isTop ? CubeFace::face[6] : CubeFace::face[0];
		}
	}
	else if (theFace == 2)
	{
		if (loc == 1)
		{
			return isTop ? CubeFace::face[6] : CubeFace::face[0];
		}
		else if (loc == 2)
		{
			return isTop ? CubeFace::face[8] : CubeFace::face[2];
		}
	}
	else if (theFace == 3)
	{
		if (loc == 1)
		{
			return isTop ? CubeFace::face[8] : CubeFace::face[2];
		}
		else if (loc == 2)
		{
			return isTop ? CubeFace::face[2] : CubeFace::face[8];
		}
	}
	else if (theFace == 4)
	{
		if (loc == 1)
		{
			return isTop ? CubeFace::face[2] : CubeFace::face[8];
		}
		else if (loc == 2)
		{
			return isTop ? CubeFace::face[0] : CubeFace::face[6];
		}
	}
}

CubeColor CubeFace::getColors(int loc)
{
	if (loc > -1 && loc < 9)
		return CubeFace::face[loc];
	else if (loc >= 9)
	{
		// if loc too large just sub 8 from loc and getColors again
		return CubeFace::getColors(loc - 8);
	}
	else if (loc <= -1)
	{
		// if loc too small just add 8 from loc and getColors again
		return CubeFace::getColors(loc + 8);
	}
	else 
	{
		; // We shouldn't ever get here
	}

	//switch (loc)
	//{
	//case 0:
	//case 1:
	//case 2:
	//case 3:
	//case 4:
	//case 5:
	//case 6:
	//case 7:
	//case 8:
	//	return CubeFace::face[loc];
	//	break;
	//default:
	//	throw new string("Error invalid Selection");
	//	break;
	//}

}

CubeColor CubeFace::getCenter()
{
	// Return the center color
	return CubeFace::getColors(4);
}

void CubeFace::setColor(CubeColor c, int loc)
{
	CubeFace::face[loc] = c;
}

void CubeFace::setColors(CubeFace theFace)
{

}

void CubeFace::setColors(vector<CubeColor> colors)
{
	for (int i = 0; i < colors.size(); i++)
	{
		CubeFace::face[i] = colors.at(i);
	}
	return;
}

void CubeFace::setColors(vector<CubeColor> colors, Mat image)
{
	int centerY = image.rows / 2;
	int centerX = image.cols / 2;

	int x, y;

	for (int i = 0; i < colors.size(); i++)
	{
		x = colors.at(i).getXPos();
		y = colors.at(i).getYPos();

		// Top Left Color
		if (x > centerX - 148 && x < centerX - 52 &&
			y > centerY - 148 && y < centerY - 52)
		{
			CubeFace::face[0] = colors.at(i);
		}
		// Top Middle Color
		else if (x > centerX - 48 && x < centerX + 48 &&
			y > centerY - 148 && y < centerY - 52)
		{
			CubeFace::face[1] = colors.at(i);
		}
		// Top Right Color
		else if (x > centerX + 52 && x < centerX + 148 &&
			y > centerY - 148 && y < centerY - 52)
		{
			CubeFace::face[2] = colors.at(i);
		}
		// Center Left Color
		else if (x > centerX - 148 && x < centerX - 52 &&
			y > centerY - 48 && y < centerY + 48)
		{
			CubeFace::face[3] = colors.at(i);
		}
		// Center Middle Color
		else if (x > centerX - 48 && x < centerX + 48 &&
			y > centerY - 48 && y < centerY + 48)
		{
			CubeFace::face[4] = colors.at(i);
		}
		// Center Right Color
		else if (x > centerX + 52 && x < centerX + 148 &&
			y > centerY - 48 && y < centerY + 48)
		{
			CubeFace::face[5] = colors.at(i);

		}
		// Bottom Left Color
		else if (x > centerX - 148 && x < centerX - 52 &&
			y > centerY + 52 && y < centerY + 148)
		{
			CubeFace::face[6] = colors.at(i);
		}
		// Bottom Middle Color
		else if (x > centerX - 48 && x < centerX + 48 &&
			y > centerY + 52 && y < centerY + 148)
		{
			CubeFace::face[7] = colors.at(i);
		}
		// Bottom Right Color
		else if (x > centerX + 52 && x < centerX + 148 &&
			y > centerY + 52 && y < centerY + 148)
		{
			CubeFace::face[8] = colors.at(i);
		}

	}

}

void CubeFace::displayFace()
{
	cout << "+---+---+---+" << endl;
	cout << "| " << face[0].getType().at(0) << " | " << face[1].getType().at(0) << " | " << face[2].getType().at(0) << " | " << endl;
	cout << "+---+---+---+" << endl;
	cout << "| " << face[3].getType().at(0) << " | " << face[4].getType().at(0) << " | " << face[5].getType().at(0) << " | " << endl;
	cout << "+---+---+---+" << endl;
	cout << "| " << face[6].getType().at(0) << " | " << face[7].getType().at(0) << " | " << face[8].getType().at(0) << " | " << endl;
	cout << "+---+---+---+" << endl;
	cout << endl;
}