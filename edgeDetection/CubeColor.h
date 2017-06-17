#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

class CubeColor
{
public:
	CubeColor();
	~CubeColor();
	
	CubeColor(string theColor, int loc);

	int getXPos();
	void setXPos(int x);

	int getYPos();
	void setYPos(int y);

	string getType();
	void setType(string theColor);

	char getTypeChar();

	Scalar getHSVmin();
	void setHSVmin(Scalar min);

	Scalar getHSVmax();
	void setHSVmax(Scalar max);

	Scalar getColor() { return color; }
	void setColor(Scalar c) { color = c; }

private:
	int xPos, yPos;
	string type;
	Scalar HSVmin, HSVmax;
	Scalar color;

};

