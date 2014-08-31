/*
 * MostrarPantalla.cpp
 *
 *  Created on: 02/08/2014
 *      Author: Guillermo Villamayor
 */

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "constants.h"

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
using namespace std;
using namespace cv;


void mostrarPantalla(Mat frameInicial, vector<Point2f> corners)
{
	RNG rng(12345);
	int r = 4;
	string main_window_name = "Pantalla Principal";
	namedWindow(main_window_name, CV_WINDOW_AUTOSIZE );
	moveWindow(main_window_name, 10,10);
	if(debugL0)
	{
		for(unsigned i = 0; i<corners.size();i++)
			circle( frameInicial, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),rng.uniform(0,255)), -1, 8, 0 );
		imshow(main_window_name,frameInicial);
	}
}




