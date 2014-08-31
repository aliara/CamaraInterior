//============================================================================
// Name        : CamaraFrontal.cpp
// Author      : Guillermo Villamayor
// Version     :
// Copyright   : Your copyright notice
// Description : Cámara Interior
//============================================================================
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


int detectFace(Mat);

int main( int argc, const char** argv )
{
	string face_window_name = "Realidad";
	RNG rng(12345);
	Mat debugImage;
	Mat skinCrCbHist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);
	Mat frame;
	vector<cv::Rect> faces;
	////////////////////////////////  createCornerKernels();
	ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2), 43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);
	// Leer el video
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(camInterior);
	//cv::VideoCapture capture(argv[1]);
	if(capture)
	{
		while( true )
		{
			frame = cvQueryFrame( capture );
			cv::flip(frame, frame, 1);
//			frame.copyTo(debugImage);
			if( !frame.empty() )
			{
				cout<<(int)detectFace(frame)<<endl;
			}
			else
			{
				printf(" --(!) No se capturaron frames -- Break!");
//				break;
			}

			int c = cv::waitKey(10);
			if( (char)c == 'c' ) { exit (0); }
			if( (char)c == 'f' )
			{
				imwrite("frame.png",frame);
			}

		}
	}
	else{cout<<"Error al conectar con la camara"<<endl; return -1;}
////////////////////////////////////////////  releaseCornerKernels();
	return 0;
}

