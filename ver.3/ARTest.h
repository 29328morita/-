#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<opencv2/opencv.hpp>

#include <opencv2/aruco.hpp>		// aruco mARKER
//#include <opencv2/aruco/charuco.hpp>



#ifdef _DEBUG
#pragma comment(lib,"opencv_world460d.lib")
#else
#pragma comment(lib,"opencv_world460.lib")
#endif


#define MARKER_SIZE 0.14800

#define MARKERIdsNumber 30
#define MARKER00_X 0
#define MARKER00_Y 0
#define MARKER01_X 0 
#define MARKER01_Y 0
#define MARKER02_X 0
#define MARKER02_Y 0
#define MARKER03_X 0
#define MARKER03_Y 0
#define MARKER04_X 0
#define MARKER04_Y 0
#define MARKER05_X 0
#define MARKER05_Y 0
#define MARKER06_X 0 
#define MARKER06_Y 0
#define MARKER07_X 0
#define MARKER07_Y 0
#define MARKER08_X 0
#define MARKER08_Y 0
#define MARKER09_X 0
#define MARKER09_Y 0
#define MARKER10_X 0
#define MARKER10_Y 0
#define MARKER11_X 0
#define MARKER11_Y 0
#define MARKER12_X 0
#define MARKER12_Y 0
#define MARKER13_X 0
#define MARKER13_Y 0
#define MARKER14_X 0
#define MARKER14_Y 0
#define MARKER15_X 0
#define MARKER15_Y 0
#define MARKER16_X 0
#define MARKER16_Y 0
#define MARKER17_X 0
#define MARKER17_Y 0
#define MARKER18_X 0
#define MARKER18_Y 0
#define MARKER19_X 0
#define MARKER19_Y 0
#define MARKER20_X 0
#define MARKER20_Y 0
#define MARKER21_X 0
#define MARKER21_Y 0
#define MARKER22_X 0
#define MARKER22_Y 0
#define MARKER23_X 0
#define MARKER23_Y 0
#define MARKER24_X 0
#define MARKER24_Y 0
#define MARKER25_X 0
#define MARKER25_Y 0
#define MARKER26_X 0
#define MARKER26_Y 0
#define MARKER27_X 0
#define MARKER27_Y 0
#define MARKER28_X 0
#define MARKER28_Y 0
#define MARKER29_X 0
#define MARKER29_Y 0

//marker_size [m]

#define MARKER00_SIZE 0.14800
#define MARKER01_SIZE 0.14800
#define MARKER02_SIZE 0.14800
#define MARKER03_SIZE 0.14800
#define MARKER04_SIZE 0.14800
#define MARKER05_SIZE 0.14800
#define MARKER06_SIZE 0.14800
#define MARKER07_SIZE 0.14800
#define MARKER08_SIZE 0.14800
#define MARKER09_SIZE 0.14800
#define MARKER10_SIZE 0.14800

#define MARKER11_SIZE 0.14800
#define MARKER12_SIZE 0.14800
#define MARKER13_SIZE 0.14800
#define MARKER14_SIZE 0.14800
#define MARKER15_SIZE 0.14800
#define MARKER16_SIZE 0.14800
#define MARKER17_SIZE 0.14800
#define MARKER18_SIZE 0.14800
#define MARKER19_SIZE 0.14800
#define MARKER20_SIZE 0.14800

#define MARKER21_SIZE 0.14800
#define MARKER22_SIZE 0.14800
#define MARKER23_SIZE 0.14800
#define MARKER24_SIZE 0.14800
#define MARKER25_SIZE 0.14800
#define MARKER26_SIZE 0.14800
#define MARKER27_SIZE 0.14800
#define MARKER28_SIZE 0.14800
#define MARKER29_SIZE 0.14800




class ARMarker
{
	private:
		cv::Ptr<cv::aruco::Dictionary> dictionary;
		cv::Mat cameraMatrix640_480;
		cv::Mat cameraMatrix480_360;
		cv::Mat distCoeffs640_480;
		cv::Mat distCoeffs480_360;


		class markerPosition
		{
		public:
			float x, y, markerSize;
		}markerPosition[MARKERIdsNumber];



		

	public:
		ARMarker();

		//class------------------------------------------------------
		//最終出力
		class ARMarkerToEstimationParameter {
		public:
			float x, y, z, yaw, pitch, roll;
		}ARMarkerToEstimaitonPrm;

		//-----------------------------------------------------------


		//func-------------------------------------------------------
		cv::Mat getCameraMatrix640_480();
		cv::Mat getCameraMatrix480_360();
		cv::Mat getDistCoeffs640_480();
		cv::Mat getDistCoeffs480_360();
		float getMarkerPositionX(uint8_t id);
		float getMarkerPositionY(uint8_t id);
		float getMarkerSize(uint8_t id);
		cv::Ptr<cv::aruco::Dictionary> getArucoDictionary();


		cv::Mat getImageMat(cv::VideoCapture inputVideo);
		cv::Mat zahyouEstimation(ARMarkerToEstimationParameter* Prm,  cv::Mat inputMat, ARMarker *AR);
		void displayImage(cv::Mat image);  //!!!画像表示のため10msの遅延関数が含まれているので注意!!!
		void videoSetup(cv::VideoCapture* inputVideo);

		//void displayPrm(ARMarker* AR)
		//-----------------------------------------------------------





};
