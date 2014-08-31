/*
 * constants.h
 *
 *  Created on: 02/08/2014
 *      Author: Guillermo Villamayor
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//Camaras
const int camInterior = 0;

//Features Shi-Tomasi
const bool ShiTomasi = true;
const double qualityLevel = 0.01;
const double minDistance = 10;
const int blockSize = 3;
const bool useHarrisDetector = false;
const double k = 0.04;


//Features Harris
const bool Harris = false;
const int threshHarris = 180;

//Markers

const double fontScale = 0.5;
const int thickness = 0.5;

//Files
const cv::String lbpName = "../resources/lbpcascade_frontalface.xml";
const cv::String haarName1 = "../resources/haarcascade_frontalface_alt.xml";
const cv::String haarName2 = "../resources/haarcascade_frontalface_alt2.xml";
const cv::String haarName3 = "../resources/haarcascade_frontalface_default.xml";
const cv::String haarName4 = "../resources/haarcascade_frontalface_alt_tree.xml";

//Debug
const bool debugL0=true;
const bool debugL1=true;
const bool debugL2=false;
const bool debugL3=false;




#endif /* CONSTANTS_H_ */
