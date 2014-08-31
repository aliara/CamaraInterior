/*
 * detectFace.cpp

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

//vector<Point2f> cornerHarris_demo( int, void*, Mat);
vector<Point2f> goodFeaturesToTrack_Demo(int, void*, Mat);
void mostrarPantalla(Mat, vector<Point2f>);
vector<Point2f> cambiarescala(vector<Point2f>, int, int);



int detectFace(Mat frameInicial)
{

	vector<Point2f> corners,imgcorners,imgrect;
	String face_cascade_name = haarName2;
	CascadeClassifier face_cascade;
	static std::vector<cv::Rect> faces;
	uint8_t dev= -1;
	Mat faceImg;
	static bool face=false;


	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error cargando la base de datos.\n"); return -1; };


	std::vector<cv::Mat> rgbChannels(3);
	split(frameInicial, rgbChannels);
	Mat frame_gray = rgbChannels[2];
	if (!face)
	{
		face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );
		cout<< "Ejecutando el Haar"<<endl;
	}
	if (faces.size() > 0)
	{
		face=true;
		vector<RotatedRect> box( corners.size() );
		for( unsigned i = 0; i < faces.size(); i++ )
		{
			rectangle(frameInicial, faces[i], 1234);
//			if(ShiTomasi && Harris){cout <<"Modificar laconfiguracion debe elegir ShiTomasi o Harris"<<endl; return 1;}
//			if(Harris)corners = cornerHarris_demo(0,0,frame_gray(cvRect(faces[i].x,faces[i].y, faces[i].width, faces[i].height)));
			corners = goodFeaturesToTrack_Demo(0,0,frame_gray(cvRect(faces[i].x,faces[i].y, faces[i].width, faces[i].height)));
			RotatedRect box = minAreaRect(Mat(corners[1]));
//			imgrect=cambiarescala(corners,faces[i].x,faces[i].y);
//			for( i = 0; i < 4; i++ )
//				line(img, vtx[i], vtx[(i+1)%4], Scalar(0, 255, 0), 1, CV_AA);
			imgcorners = cambiarescala(corners,faces[i].x,faces[i].y);
		}
		cout<<"Cantidad de corners: "<<corners.size()<<"	"<<"face:"<<face<<endl;
//		if(corners.size()<5) face=false;

	//-- Show what you got

		//		  rectangle(frameInicial, faces[i], 1234);
		///////////////////////dev = findEyes(frame_gray, faces[0]);
	}
	if (faces.size()==0)
	{
		face = false;
		putText(frameInicial, "No se detecto la cara", cvPoint(30,30), 1, 0.8, cvScalar(200,200,250), 1, 0);
		dev=0;
	}
	//corners = goodFeaturesToTrack_Demo(0,0,frame_gray);
	//imgcorners = cambiarescala(corners,10,10);
	mostrarPantalla(frameInicial,imgcorners);

	return dev;
}


vector<Point2f> cambiarescala(vector<Point2f> corners, int x, int y)
{
	for (unsigned i = 0; i<corners.size();i++)
	{
		corners[i].x=corners[i].x+x;
		corners[i].y=corners[i].y+y;
	}
	return corners;
}

