#include "CubeFace.h"



CubeFace::CubeFace()
{
}


CubeFace::~CubeFace()
{
	//delete[] face;
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