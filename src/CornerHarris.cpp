/*
 * CornerHarris.cpp

 *
 *  Created on: 02/08/2014
 *      Author: Guillermo Villamayor
 */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

using namespace cv;
using namespace std;



//char* source_window = "Source image";



vector<Point2f> cornerHarris_demo( int, void*, Mat src_gray)
{
	Mat src;

	//int max_thresh = 255;
	string corners_window = "Puntos detectados";
	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros( src.size(), CV_32FC1 );
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	vector<Point2f> corners;

	/// Detector parameters
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;

	/// Detecting corners
	cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

	/// Normalizing
	normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs(dst_norm, dst_norm_scaled);
	//Mat srcMat = cv::Mat(cornersint);
	//Mat dstMat = cv::Mat(dst);
	//Mat tmpMat;
	//dst_norm_scaled.convertTo(tmpMat, dstMat.type());

	int cont = 0;

	/// Drawing a circle around corners
	for( int j = 0; j < dst_norm.rows ; j++ )
	{
		for( int i = 0; i < dst_norm.cols; i++ )
		{
			if( (int) dst_norm.at<float>(j,i) > threshHarris )
			{
				//circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
				putText(dst, "+", Point(i,j), fontFace, fontScale, Scalar::all(255), thickness,8);
				corners.push_back(Point(i,j));
				cont++;
			}
		}
	}

	if (debugL1)
	{
		/// Showing the result
		namedWindow( corners_window, CV_WINDOW_AUTOSIZE );
		moveWindow(corners_window,500,10);
		imshow( corners_window, dst_norm_scaled );
	}

	return corners;
}




