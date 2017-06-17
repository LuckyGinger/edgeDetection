//winCubeSolver

//Written by  Thom Allen  2017

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
//, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//IN THE SOFTWARE.

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "CubeColor.h"
#include "CubeFace.h"
#include "CubeCube.h"


//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 0;
int H_MAX = 179;
int S_MIN = 0;
int S_MAX = 255;
int V_MIN = 0;
int V_MAX = 255;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 9;
const int MAX_NOISE = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 100 * 10;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";

// Click Button
Mat3b canvas;
string buttonText = "Set Face";
string winName = "My cool button GUI v0.1";
Rect button;

CubeCube cube;
CubeFace face;

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed





}
string intToString(int number) {


	std::stringstream ss;
	ss << number;
	return ss.str();
}

void drawLines(Mat image)
{
	// draw Cube lines on live feed

	int centerY = image.rows / 2;
	int centerX = image.cols / 2;


	for (int y = 0; y < image.rows; y++) // y = rows
	{

		for (int x = 0; x < image.cols; x++) // x = cols
		{

			Vec3b bgrPixel = image.at<Vec3b>(y, x);

			// White Cross Section lines
			if ((x == centerX - 51 || x == centerX - 50 || x == centerX - 49 ||
				x == centerX + 51 || x == centerX + 50 || x == centerX + 49 ||
				y == centerY - 51 || y == centerY - 50 || y == centerY - 49 ||
				y == centerY + 51 || y == centerY + 50 || y == centerY + 49) &&
				x >= centerX - 151 && x <= centerX + 151 &&
				y >= centerY - 151 && y <= centerY + 151)
			{
				bgrPixel[0] = 255;
				bgrPixel[1] = 255;
				bgrPixel[2] = 255;

				image.at<Vec3b>(y, x) = bgrPixel;
			}

			// White Border lines
			if ((x == centerX - 151 || x == centerX - 150 || x == centerX - 149 ||
				x == centerX + 151 || x == centerX + 150 || x == centerX + 149 ||
				y == centerY - 151 || y == centerY - 150 || y == centerY - 149 ||
				y == centerY + 151 || y == centerY + 150 || y == centerY + 149) &&
				x >= centerX - 151 && x <= centerX + 151 &&
				y >= centerY - 151 && y <= centerY + 151)
			{
				bgrPixel[0] = 255;
				bgrPixel[1] = 255;
				bgrPixel[2] = 255;

				image.at<Vec3b>(y, x) = bgrPixel;
			}

		}

	}

	return;
}

void createTrackbars() {
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);


}
void drawObject(vector<CubeColor> theColors, Mat &frame, double area) {

	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!

	//UPDATE:JUNE 18TH, 2013
	//added 'if' and 'else' statements to prevent
	//memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

	for (int i = 0; i < theColors.size(); i++)
	{
		//circle(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), 20, Scalar(0, 255, 0), 2);
		circle(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), 10, theColors.at(i).getColor(), 2);
		//if (theColors.at(i).getYPos() - 25>0)
		//	line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() - 25), Scalar(0, 255, 0), 2);
		//else line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(theColors.at(i).getXPos(), 0), Scalar(0, 255, 0), 2);
		//if (theColors.at(i).getYPos() + 25<FRAME_HEIGHT)
		//	line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() + 25), Scalar(0, 255, 0), 2);
		//else line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(theColors.at(i).getXPos(), FRAME_HEIGHT), Scalar(0, 255, 0), 2);
		//if (theColors.at(i).getXPos() - 25>0)
		//	line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(theColors.at(i).getXPos() - 25, theColors.at(i).getYPos()), Scalar(0, 255, 0), 2);
		//else line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(0, theColors.at(i).getYPos()), Scalar(0, 255, 0), 2);
		//if (theColors.at(i).getXPos() + 25<FRAME_WIDTH)
		//	line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(theColors.at(i).getXPos() + 25, theColors.at(i).getYPos()), Scalar(0, 255, 0), 2);
		//else line(frame, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), Point(FRAME_WIDTH, theColors.at(i).getYPos()), Scalar(0, 255, 0), 2);

		putText(frame, intToString(theColors.at(i).getXPos()) + "," + intToString(theColors.at(i).getYPos()), Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() + 30), 1, 1, theColors.at(i).getColor(), 2);
		putText(frame, intToString(area), Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() + 50), 1, 1, theColors.at(i).getColor(), 2);
		putText(frame, theColors.at(i).getType(), Point(theColors.at(i).getXPos()-30, theColors.at(i).getYPos() - 15), 1, 2, theColors.at(i).getColor(), 2);

	}


}

void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5, 5));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);



}

void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed) {

	vector <CubeColor> colors;
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	int counter = 0;
	string error = "";

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		double area = 0;

		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<=MAX_NOISE) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				//if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {
				if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA) {
					CubeColor color;
					
					color.setXPos(moment.m10 / area);
					color.setYPos(moment.m01 / area);
					objectFound = true;
					refArea = area;
				
					colors.push_back(color);
					counter++;
				}
				else if (area<MIN_OBJECT_AREA) {
					objectFound = false;
					error = "area < MIN_OBJECT_AREA";
				}
				else if (area > MAX_OBJECT_AREA) {
					objectFound = false;
					error = "area > MAX_OBJECT_AREA";
				}
				else if (area < refArea) {

				}
				else {
					objectFound = false;

				}


			}

			//let user know you found an object
			if (objectFound == true) {
				putText(cameraFeed, "Tracking Objects " + to_string(counter), Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
				//draw object location on screen
				drawObject(colors, cameraFeed, area);
			}
			else {
				putText(cameraFeed, error, Point(0, 50), 2, 1, Scalar(80, 127, 255), 2);

			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}

void trackFilteredObject(CubeColor theColor, int &x, int &y, Mat threshold, Mat &cameraFeed) {

	vector <CubeColor> colors;
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	int counter = 0;
	string error = "";

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		double area = 0;

		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects <= MAX_NOISE) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				//if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {
				if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA) {
					CubeColor color;

					color.setXPos(moment.m10 / area);
					color.setYPos(moment.m01 / area);
					color.setType(theColor.getType());
					color.setColor(theColor.getColor());

					objectFound = true;
					refArea = area;

					colors.push_back(color);
					counter++;
				}
				else if (area<MIN_OBJECT_AREA) {
					objectFound = false;
					error = "area < MIN_OBJECT_AREA";
				}
				else if (area > MAX_OBJECT_AREA) {
					objectFound = false;
					error = "area > MAX_OBJECT_AREA";
				}
				else if (area < refArea) {
					objectFound = false;
					error = "area < refArea";
				}
				else {
					error = "Something is going wrong";
					objectFound = false;

				}


			}

			//let user know you found an object
			if (objectFound == true) {
				putText(cameraFeed, "Tracking Objects " + to_string(counter), Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
				//draw object location on screen
				drawObject(colors, cameraFeed, area);
				// todo: set up color counting
				// todo: set up building cubeface
				//setColors(CubeColor color, Mat image)

			}
			else {
				putText(cameraFeed, error, Point(0, 50), 2, 1, Scalar(80, 127, 255), 2);

			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}

void trackFilteredObject(CubeFace &face, CubeColor theColor, int &x, int &y, Mat threshold, Mat &cameraFeed) {

	vector <CubeColor> colors;
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	int counter = 0;
	string error = "";

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		double area = 0;

		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects <= MAX_NOISE) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				//if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {
				if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA) {
					CubeColor color;

					color.setXPos(moment.m10 / area);
					color.setYPos(moment.m01 / area);
					color.setType(theColor.getType());
					color.setColor(theColor.getColor());

					objectFound = true;
					refArea = area;

					colors.push_back(color);
					counter++;
				}
				else if (area<MIN_OBJECT_AREA) {
					objectFound = false;
					//error = "area < MIN_OBJECT_AREA";
				}
				else if (area > MAX_OBJECT_AREA) {
					objectFound = false;
					//error = "area > MAX_OBJECT_AREA";
				}
				else if (area < refArea) {
					objectFound = false;
					//error = "area < refArea";
				}
				else {
					//error = "Something is going wrong";
					objectFound = false;

				}


			}

			//let user know you found an object
			if (objectFound == true) {
				//putText(cameraFeed, "Tracking Objects " + to_string(counter), Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
				//draw object location on screen
				drawObject(colors, cameraFeed, area);
				// todo: set up color counting
				// todo: set up building cubeface
				face.setColors(colors, cameraFeed);

			}
			else {
				//putText(cameraFeed, error, Point(0, 50), 2, 1, Scalar(80, 127, 255), 2);

			}

		}
		//		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (button.contains(Point(x, y)))
		{
			cout << "Clicked!" << endl;
			cube.setFace(face);

			rectangle(canvas(button), button, Scalar(0, 0, 255), 2);
		}
	}
	if (event == EVENT_LBUTTONUP)
	{
		rectangle(canvas, button, Scalar(200, 200, 200), 2);
	}

	imshow(winName, canvas);
	waitKey(1);
}

void clickFace()
{
	// An image
	Mat3b img(300, 300, Vec3b(0, 255, 0));

	// Your button
	button = Rect(0, 0, img.cols, 50);

	// The canvas
	canvas = Mat3b(img.rows + button.height, img.cols, Vec3b(0, 0, 0));

	// Draw the button
	canvas(button) = Vec3b(200, 200, 200);
	putText(canvas(button), buttonText, Point(button.width*0.35, button.height*0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));

	// Draw the image
	img.copyTo(canvas(Rect(0, button.height, img.cols, img.rows)));

	// Setup callback function
	namedWindow(winName);
	setMouseCallback(winName, callBackFunc);

	imshow(winName, canvas);

}


int main(int argc, char* argv[])
{
	int cam = 1;
	int loc = 1; // 0 = myApt, 1 = Campus, 3 = Not set

	CubeColor color;
	
	clickFace();

	//some boolean variables for different functionality within this
	//program
	bool trackObjects = true;
	bool useMorphOps = true;
	bool calibrationMode = false;
	//Matrix to store each frame of the webcam feed
	Mat cameraFeed;
	Mat cameraShow;
	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	Mat threshold2;
	//create slider bars for HSV filtering
	createTrackbars();

	//x and y values for the location of the object
	int x = 0, y = 0;
	//video capture object to acquire webcam feed
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	capture.open(cam);
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	
	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	int faceCounter = 0;
	CubeFace tempFace;
	bool isFirstPass = true;
	while (1) {
		//store image to matrix
		capture.read(cameraFeed);
		capture.read(cameraShow);
		drawLines(cameraShow);
		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

		if (calibrationMode == true)
		{

			color.setHSVmin(Scalar(H_MIN, S_MIN, V_MIN));
			color.setHSVmax(Scalar(H_MAX, S_MAX, V_MAX));
			
			//filter HSV image between values and store filtered image to
			//threshold matrix
			inRange(HSV, color.getHSVmin(), color.getHSVmax(), threshold);
			//inRange(cameraFeed, Scalar(180 + H_MIN, S_MIN, V_MIN), Scalar( 180 + H_MAX, S_MAX, V_MAX), threshold2);
			//threshold = threshold | threshold2;


			// Perform morphological operations on thresholded image to eliminate noise
			//  and emphasize the filtered object(s)morphOps(threshold);
			morphOps(threshold);
			// Display threshold
			imshow(windowName2, threshold);
			// This function will return the x and y coordinates of the
			//  filtered object
			trackFilteredObject(color, x, y, threshold, cameraShow);
			//trackFilteredObject(color, x, y, threshold, cameraFeed);
		}
		else {
			CubeColor red("red", loc), green("green", loc), blue("blue", loc);
			CubeColor white("white", loc), orange("orange", loc), yellow("yellow", loc);

			//CubeColor green("green");
			//CubeColor yellow("yellow");

			//red.setHSVmin(Scalar(0, 224, 151));
			//red.setHSVmax(Scalar(25, 256, 234));

			// RED COLOR
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			inRange(HSV, red.getHSVmin(), red.getHSVmax(), threshold);
			morphOps(threshold);
			//imshow(windowName2, threshold);
			trackFilteredObject(face, red, x, y, threshold, cameraShow);


			// GREEN COLOR
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			inRange(HSV, green.getHSVmin(), green.getHSVmax(), threshold);
			morphOps(threshold);
			trackFilteredObject(face, green, x, y, threshold, cameraShow);

			// BLUE COLOR
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			inRange(HSV, blue.getHSVmin(), blue.getHSVmax(), threshold);
			morphOps(threshold);
			trackFilteredObject(face, blue, x, y, threshold, cameraShow);

			// WHITE COLOR
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			inRange(HSV, white.getHSVmin(), white.getHSVmax(), threshold);
			morphOps(threshold);
			trackFilteredObject(face, white, x, y, threshold, cameraShow);

			// ORANGE COLOR
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			inRange(HSV, orange.getHSVmin(), orange.getHSVmax(), threshold);
			morphOps(threshold);
			trackFilteredObject(face, orange, x, y, threshold, cameraShow);
			

			// YELLOW COLOR
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			inRange(HSV, yellow.getHSVmin(), yellow.getHSVmax(), threshold);
			morphOps(threshold);
			trackFilteredObject(face, yellow, x, y, threshold, cameraShow);

			//cube.displayClick();
			//clickFace();
			
			//if (isFirstPass)
			//{
			//	tempFace = face;
			//	isFirstPass = false;
			//}


		}
		


		//show frames 
		//imshow(windowName2, threshold);
		imshow(windowName, cameraFeed);
		imshow("Main Display", cameraShow);
		imshow(windowName1, HSV);


		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		if (cvWaitKey(30)!=-1) {
			break;
		}
		//face.displayFace();
		cube.displayCube();
	}




	destroyAllWindows();

	return 0;
}
