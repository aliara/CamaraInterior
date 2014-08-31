/*
 * ShiTomasi.cpp
 *
 *  Created on: 02/08/2014
 *      Author: Guillermo Villamayor
 */
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

using namespace cv;
using namespace std;







vector<Point2f> goodFeaturesToTrack_Demo( int , void*, Mat src_gray )
{
	int maxCorners = 23;
	if( maxCorners < 1 ) { maxCorners = 1; }
	RNG rng(12345);
	string corners_window = "Puntos detectados";
	TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
	Size winSize(10,10);

	/// Parametros del algoritmo Shi-Tomasi
	vector<Point2f> corners[2];// El [0] son los puntos anteriores y el [1] son los actuales






	Mat copy,prev_gray;
	copy = src_gray.clone();

	/// Detectar puntos
	goodFeaturesToTrack( src_gray,
               corners[1],
               maxCorners,
               qualityLevel,
               minDistance,
               Mat(),
               blockSize,
               useHarrisDetector,
               k );
	cornerSubPix(src_gray, corners[1], winSize, Size(-1,-1), termcrit);
	vector<uchar> status;
	vector<float> err;
	if(prev_gray.empty()) src_gray.copyTo(prev_gray);
	cout<<"Corners[0] = "<<corners[0].empty()<<endl;

	if( !corners[0].empty() )
	{
		cout<<"siguiendo"<<endl;
		calcOpticalFlowPyrLK(prev_gray, src_gray, corners[0], corners[1], status, err, winSize, 3, termcrit, 0);
		size_t i, k;
		/// Marcar los puntos detectados
		if(debugL1)
		{
			namedWindow( corners_window, CV_WINDOW_AUTOSIZE );
			moveWindow(corners_window,600,10);
			cout<<"** Numero de puntos detectados: "<<corners[1].size()<<endl;
			int r = 4;
			for( unsigned i = 0; i < corners[1].size(); i++ )
			{
				circle( copy, corners[1][i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),rng.uniform(0,255)), -1, 8, 0 );
				//circle( copy, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),rng.uniform(0,255)), -1, 8, 0 );
			}

			imshow( corners_window, copy );
		}
	}
	std::swap(corners[1], corners[0]);
	swap(prev_gray, src_gray);
	return corners[0];
}




