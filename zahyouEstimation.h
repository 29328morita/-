#pragma once


#pragma once


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<opencv2/opencv.hpp>

#include <opencv2/aruco.hpp>		// aruco marker
//#include <opencv2/aruco/charuco.hpp>



#ifdef _DEBUG
#pragma comment(lib,"opencv_world460d.lib")
#else
#pragma comment(lib,"opencv_world460.lib")
#endif



#define MarkerIdsNumber 13
#define Marker00_x 0
#define Marker00_y 0
#define Marker01_x 0 
#define Marker01_y 0
#define Marker02_x 0
#define Marker02_y 0
#define Marker03_x 0
#define Marker03_y 0
#define Marker04_x 0
#define Marker04_y 0
#define Marker05_x 0
#define Marker05_y 0
#define Marker06_x 0 
#define Marker06_y 3
#define Marker07_x 0
#define Marker07_y 2
#define Marker08_x 0
#define Marker08_y 1
#define Marker09_x 0
#define Marker09_y 0
#define Marker10_x 0
#define Marker10_y 0
#define Marker11_x 0
#define Marker11_y 0
#define Marker12_x 0
#define Marker12_y 0









//camera init
//bool cameraSetup()
//{
//
//
//
//}


//markerPosition markerPositionInit(int8_t id, float x, float y)
//{
//    markerPosition MP;
//    MP.markerId = id;
//    MP.x = x;
//    MP.y = y;
//    return MP;
//}



