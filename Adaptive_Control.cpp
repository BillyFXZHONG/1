#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

using namespace cv;
using namespace std;

double a = 10.0;
double b = 5.0;
double ae = 0.0;
double be = 0.0;

double x1 = 2.0;
double x2 = 2.0;
double y = 0.0;
double ye = 0.0;
double e = 0.0;

double eQea = 0.0;
double eQeb = 0.0;
double daedt = 0.0;
double dbedt = 0.0;

double Q = 0.0;

double k = 0.005;

bool PAUSE = false;

int _step = 40;
int counter = 0;

vector<Point2f> points;
vector<Point2f> points1;

string intToString(double number)							//change the int number to string output on the image
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}


int main()
{	
	
	namedWindow("Visualization", 0);
	cvMoveWindow("Visualization", 0, 0);
	cvResizeWindow("Visualization", 1000, 400);

	while(1) {

	Mat data (400, 1000, CV_8UC3, Scalar(100,100,100));

	y = a*pow(x1, 2) + b*pow(x2, 2);	//The true measures results containing the true values of the system
	ye = ae*pow(x1, 2) + be*pow(x2, 2); 			//The estimated result using estimated parameters

	e = ye - y;					//Obtain the estimation error like this

	Q = 0.5*pow(e, 2);		//Define the quadratic energy function

	eQea = ae*pow(x1, 4) + be*pow(x1, 2)*pow(x2, 2) - y*pow(x1, 2);			//Derivative of Q to ae
	eQeb = be*pow(x2, 4) + ae*pow(x1, 2)*pow(x2, 2) - y*pow(x2, 2);

	daedt = -k*eQea;		//The final update rule for the unknown parameter ae
	dbedt = -k*eQeb;

	ae += daedt;
	be += dbedt;

	line(data, Point2f(0, 300), Point2f(1000, 300), Scalar(0,0,80), 2);

	for (int i = 0; i < points.size(); i++)
	{
		circle(data, points1[i], 3, Scalar(0,222,155), 2, 8);
		circle(data, points[i], 3, Scalar(0,0,255), 2, 8);
		
	}

	//putText(data, "x: " + intToString(x1) + "", Point2f(450, 20), 1,1, CV_RGB(255,255,255),2);
	putText(data, "ae: " + intToString(ae) + "", Point2f(450, 45), 1,1, CV_RGB(255,255,255),2);
	putText(data, "be: " + intToString(be) + "", Point2f(450, 70), 1,1, CV_RGB(255,255,255),2);
	putText(data, "Q: " + intToString(Q) + "", Point2f(450, 95), 1,1, CV_RGB(255,255,255),2);
	putText(data, "ye= " + intToString(ye) + "", Point2f(450, 120), 1,1, CV_RGB(255,255,255),2);
	putText(data, "y = " + intToString(y) + "", Point2f(450, 145), 1,1, CV_RGB(255,255,255),2);

	points.push_back(Point2f(counter*2, ae*30));
	points1.push_back(Point2f(counter*2, be*30));

	///////////////////////////////////////////////////////////



	counter++;

	imshow("Visualization", data);

	char c = (char)waitKey(_step);
	if(c == 27)
		return -1;
	else if (c == 'p') {

		PAUSE = true;
		while (PAUSE)
		{
			char d = (char)waitKey(1);
			if (d == 'p')
				PAUSE = false;
			else if (d == 27)
				return -1;
		}
	}

	}
	return 0;
}