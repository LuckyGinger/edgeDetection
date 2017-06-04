#include "CubeColor.h"



CubeColor::CubeColor()
{
	setType("color!set");
	setColor(Scalar(0, 255, 0));
}

CubeColor::CubeColor(string theColor, int loc)
{
	setType(theColor);

	if (theColor == "red") {
		if (loc == 0) {			
			setHSVmin(Scalar(0, 0, 100));
			setHSVmax(Scalar(53, 35, 179));
		}
		else if (loc == 1) {
			setHSVmin(Scalar(0, 145, 80));
			setHSVmax(Scalar(9, 255, 168));
		}

		setColor(Scalar(0, 0, 255));
	}
	if (theColor == "green") {
		if (loc == 0) {
			setHSVmin(Scalar(29, 124, 0));
			setHSVmax(Scalar(195, 256, 86));
		}
		else if(loc == 1) {
			setHSVmin(Scalar(61, 182, 154));
			setHSVmax(Scalar(91, 255, 255));
		}
	
		setColor(Scalar(0, 100, 0));
	}
	if (theColor == "blue") {

		if (loc == 0) {
			setHSVmin(Scalar(151, 54, 0));
			setHSVmax(Scalar(256, 184, 75));
		}
		else if (loc == 1) {
			setHSVmin(Scalar(97, 220, 72));
			setHSVmax(Scalar(179, 255, 255));
		}

		setColor(Scalar(139, 0, 0));
	}
	if (theColor == "white") {
		if (loc == 0) {
			setHSVmin(Scalar(158, 151, 112));
			setHSVmax(Scalar(256, 245, 256));
		}
		else if (loc == 1) {
			setHSVmin(Scalar(69, 40, 171));
			setHSVmax(Scalar(140, 236, 255));
		}

		setColor(Scalar(255, 255, 255));
	}
	if (theColor == "orange") {
		if (loc == 0) {
			setHSVmin(Scalar(7, 75, 196));
			setHSVmax(Scalar(160, 151, 256));
		}
		else if (loc == 1) {
			setHSVmin(Scalar(0, 173, 182));
			setHSVmax(Scalar(34, 255, 255));
		}

		setColor(Scalar(8, 75, 248));
	}
	if (theColor == "yellow") {
		if (loc == 0) {
			setHSVmin(Scalar(74, 198, 58));
			setHSVmax(Scalar(205, 256, 256));
		}
		else if (loc == 1) {
			setHSVmin(Scalar(23, 68, 182));
			setHSVmax(Scalar(64, 196, 255));
		}

		setColor(Scalar(10, 216, 255));
	}

}

CubeColor::~CubeColor()
{
}

int CubeColor::getXPos()
{
	return CubeColor::xPos;
}

void CubeColor::setXPos(int x)
{
	CubeColor::xPos = x;
}

int CubeColor::getYPos()
{
	return CubeColor::yPos;
}

void CubeColor::setYPos(int y)
{
	CubeColor::yPos = y;
}

Scalar CubeColor::getHSVmin()
{
	return CubeColor::HSVmin;
}

void CubeColor::setHSVmin(Scalar min)
{
	CubeColor::HSVmin = min;
}

Scalar CubeColor::getHSVmax()
{
	return CubeColor::HSVmax;
}

void CubeColor::setHSVmax(Scalar max)
{
	CubeColor::HSVmax = max;
}

string CubeColor::getType()
{
	return CubeColor::type;
}

void CubeColor::setType(string theColor)
{
	CubeColor::type = theColor;
}