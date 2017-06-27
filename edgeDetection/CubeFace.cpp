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

CubeColor CubeFace::getColors(int loc)
{
	switch (loc)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		return CubeFace::face[loc];
		break;
	default:
		throw new string("Error invalid Selection");
		break;
	}

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