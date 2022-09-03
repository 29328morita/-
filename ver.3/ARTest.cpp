#include "ARTest.h"

ARMarker::ARMarker()
{
	//private--------------------------------------------------------------------------------------------------------------------
	
	//ノパソ用
	//cameraMatrix640_480 = (cv::Mat_<double>(3, 3) << 736.25415, 0, 639.5, 0, 736.25415, 359.5, 0, 0, 1);
	//distCoeffs640_480 = (cv::Mat_<double>(1, 5) << -0.0155008, -0.0578324, 0, 0, 0);

	//ラズパイ
	cameraMatrix640_480 = (cv::Mat_<double>(3, 3) <<485.70642, 0, 319.5,0, 485.70642, 239.5,0, 0, 1);
	distCoeffs640_480 = (cv::Mat_<double>(1, 5) << 0.159363, -0.300482, 0, 0, 0);
	cameraMatrix480_360 = (cv::Mat_<double>(3, 3) << 296.66498, 0, 239.5,0, 296.66498, 179.5,0, 0, 1);
	distCoeffs480_360 = (cv::Mat_<double>(1, 5) << 0.0394978, -0.101765, 0, 0, 0);
	dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);




	markerPosition[0] = { MARKER00_X,MARKER00_Y,MARKER00_SIZE };
	markerPosition[1] = { MARKER01_X,MARKER01_Y ,MARKER01_SIZE};
	markerPosition[2] = { MARKER02_X,MARKER02_Y ,MARKER02_SIZE };
	markerPosition[3] = { MARKER03_X,MARKER03_Y ,MARKER03_SIZE };
	markerPosition[4] = { MARKER04_X,MARKER04_Y ,MARKER04_SIZE };
	markerPosition[5] = { MARKER05_X,MARKER05_Y ,MARKER05_SIZE };
	markerPosition[6] = { MARKER06_X,MARKER06_Y ,MARKER06_SIZE };
	markerPosition[7] = { MARKER07_X,MARKER07_Y ,MARKER07_SIZE };
	markerPosition[8] = { MARKER08_X,MARKER08_Y ,MARKER08_SIZE };
	markerPosition[9] = { MARKER09_X,MARKER09_Y ,MARKER09_SIZE };
	markerPosition[10] = { MARKER10_X,MARKER10_Y ,MARKER10_SIZE };
	markerPosition[11] = { MARKER11_X,MARKER11_Y ,MARKER11_SIZE };
	markerPosition[12] = { MARKER12_X,MARKER12_Y ,MARKER12_SIZE };
	markerPosition[13] = { MARKER13_X,MARKER13_Y ,MARKER13_SIZE };
	markerPosition[14] = { MARKER14_X,MARKER14_Y ,MARKER14_SIZE };
	markerPosition[15] = { MARKER15_X,MARKER15_Y ,MARKER15_SIZE };
	markerPosition[16] = { MARKER16_X,MARKER16_Y ,MARKER16_SIZE };
	markerPosition[17] = { MARKER17_X,MARKER17_Y ,MARKER17_SIZE };
	markerPosition[18] = { MARKER18_X,MARKER18_Y ,MARKER18_SIZE };
	markerPosition[19] = { MARKER19_X,MARKER19_Y ,MARKER19_SIZE };
	markerPosition[20] = { MARKER20_X,MARKER20_Y ,MARKER20_SIZE };
	markerPosition[21] = { MARKER21_X,MARKER21_Y ,MARKER21_SIZE };
	markerPosition[22] = { MARKER22_X,MARKER22_Y ,MARKER22_SIZE };
	markerPosition[23] = { MARKER23_X,MARKER23_Y ,MARKER23_SIZE };
	markerPosition[24] = { MARKER24_X,MARKER24_Y ,MARKER24_SIZE };
	markerPosition[25] = { MARKER25_X,MARKER25_Y ,MARKER25_SIZE };
	markerPosition[26] = { MARKER26_X,MARKER26_Y ,MARKER26_SIZE };
	markerPosition[27] = { MARKER27_X,MARKER27_Y ,MARKER27_SIZE };
	markerPosition[28] = { MARKER28_X,MARKER28_Y ,MARKER28_SIZE };
	markerPosition[29] = { MARKER29_X,MARKER29_Y ,MARKER29_SIZE };
	//----------------------------------------------------------------------------------------------------------------------------


	//public----------------------------------------------------------------------------------------------------------------------
	ARMarkerToEstimaitonPrm.x = 0;
	ARMarkerToEstimaitonPrm.y = 0;
	ARMarkerToEstimaitonPrm.z = 0;
	ARMarkerToEstimaitonPrm.pitch=0;
	ARMarkerToEstimaitonPrm.roll = 0;
	ARMarkerToEstimaitonPrm.yaw = 0;



	//-----------------------------------------------------------------------------------------------------------------------------

}




cv::Mat ARMarker::getCameraMatrix640_480()
{
	return cameraMatrix640_480;
}

cv::Mat ARMarker::getCameraMatrix480_360()
{
	return cameraMatrix480_360;
}

cv::Mat ARMarker::getDistCoeffs640_480()
{
	return distCoeffs640_480;
}

cv::Mat ARMarker::getDistCoeffs480_360()
{
	return distCoeffs480_360;
}

float ARMarker::getMarkerPositionX(uint8_t id)
{
	return markerPosition[id].x;
}


float ARMarker::getMarkerPositionY(uint8_t id)
{
	return markerPosition[id].y;
}

float ARMarker::getMarkerSize(uint8_t id)
{
	return markerPosition[id].markerSize;
}

cv::Ptr<cv::aruco::Dictionary> ARMarker::getArucoDictionary()
{
	return dictionary;
}

void ARMarker::videoSetup(cv::VideoCapture* inputVideo)
{
	inputVideo->open(0);
	inputVideo->set(cv::CAP_PROP_FPS, 15);           //カメラFPSを60FPSに設定
	inputVideo->set(cv::CAP_PROP_FRAME_WIDTH, 1280);// カメラ画像の横幅を1280に設定
	inputVideo->set(cv::CAP_PROP_FRAME_HEIGHT, 720); // カメラ画像の縦幅を720に設定, 
}

cv::Mat ARMarker::getImageMat(cv::VideoCapture inputVideo)
{
	cv::Mat image;

	if (inputVideo.grab()) {
		inputVideo.retrieve(image);
	}


	return image;
}


void ARMarker::displayImage(cv::Mat image)  //!!!画像表示のため10msの遅延関数が含まれているので注意!!!
{
	cv::imshow("out", image);
	char key = (char)cv::waitKey(10);
}





//パラメータ更新&検出状況がわかるような画像(軸描画)を出力
cv::Mat ARMarker::zahyouEstimation(ARMarkerToEstimationParameter* Prm, cv::Mat inputMat,ARMarker* AR)
{

	cv::Mat imageCopy, outputArry;
	inputMat.copyTo(imageCopy);
	std::vector<int> ids;  //uint8_t だとバグる
	std::vector<std::vector<cv::Point2f>> corners;

	cv::aruco::detectMarkers(inputMat, AR->getArucoDictionary() , corners, ids);




	// if at least one marker detected
	if (ids.size() > 0) {
		std::vector<cv::Vec3d> rvecs, tvecs;
		cv::aruco::estimatePoseSingleMarkers(corners, MARKER_SIZE, AR->getCameraMatrix640_480(), AR->getDistCoeffs640_480(), rvecs, tvecs, outputArry);



		//camera座標 → marekr座標-------------------------------------------------------------------------------------------------------------------
		uint8_t kyoriGaTikai = 0; //配列のn番目
		std::vector<float> relativeDistance; //相対距離
		std::vector<cv::Mat> rvecs_Mat, tvecs_Mat, vector3_0, R, Rt, MarkerToCameraPosition;



		for (uint8_t j = 0; j < ids.size(); j++)
		{
			//初期化
			R.push_back((cv::Mat::eye(3, 3, CV_32F)));
			Rt.push_back((cv::Mat::eye(3, 3, CV_32F)));
			vector3_0.push_back((cv::Mat_<float>(1, 3) << 0, 0, 0));
			MarkerToCameraPosition.push_back((cv::Mat_<float>(1, 3) << 0, 0, 0));


			//rvecs,tvces --  std::vector → cv::Mat  (y,X)
			rvecs_Mat.push_back((cv::Mat_<float>(1, 3) << rvecs.at(j)[0], rvecs.at(j)[1], rvecs.at(j)[2]));
			tvecs_Mat.push_back((cv::Mat_<float>(1, 3) << tvecs.at(j)[0], tvecs.at(j)[1], tvecs.at(j)[2]));


			cv::Rodrigues(rvecs_Mat.at(j), Rt.at(j));
			R.at(j) = Rt.at(j).t();


			//エラー回避の関係で　縦ベクトル+他0の3*3
			tvecs_Mat.at(j) = (cv::Mat_<float>(3, 3) << tvecs.at(j)[0], 0, 0, tvecs.at(j)[1], 0, 0, tvecs.at(j)[2], 0, 0);
			MarkerToCameraPosition.at(j) = (-R.at(j)) * (tvecs_Mat.at(j));


		}
		//-------------------------------------------------------------------------------------------------------------------------------------------
		//最小距離のmarker比較-----------------------------------------------------------------------------------------------------------------------
		for (uint8_t k = 0; k < ids.size(); k++)
		{

			//相対距離の二乗比較
			relativeDistance.push_back((std::pow(MarkerToCameraPosition.at(k).at<float>(1, 0), 2) + std::pow(MarkerToCameraPosition.at(k).at<float>(1, 0), 2) + std::pow(MarkerToCameraPosition.at(k).at<float>(2, 0), 2)));
			if (k == 0)
			{
				kyoriGaTikai = 0;
			}


			if ((k != 0) && ((relativeDistance[kyoriGaTikai]) > (relativeDistance[k])))
			{
				kyoriGaTikai = k;
			}



		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		//マーカーidからマーカー固有のフィールド座標を付与  //フィールド座標=相対距離が最も近いマーカーidの座標+相対距離
		Prm->x = MarkerToCameraPosition.at(kyoriGaTikai).at<float>(0, 0) += AR->getMarkerPositionX(ids[kyoriGaTikai]);
		Prm->y = MarkerToCameraPosition.at(kyoriGaTikai).at<float>(1, 0) += AR->getMarkerPositionX(ids[kyoriGaTikai]);
		Prm->z = MarkerToCameraPosition.at(kyoriGaTikai).at<float>(2, 0);
		Prm->roll = std::atan2(static_cast<float>(-(R.at(kyoriGaTikai).at<float>(2, 1))), static_cast<float>(R.at(kyoriGaTikai).at<float>(2, 2))); //コンパイルエラー対策
		Prm->pitch = std::asin(static_cast<float>(R.at(kyoriGaTikai).at<float>(2, 0)));
		Prm->yaw = std::atan2(static_cast<float>(-(R.at(kyoriGaTikai).at<float>(1, 0))), static_cast<float>(R.at(kyoriGaTikai).at<float>(0, 0)));


		
		//出力画像---------------------------------------------------------------------------------------------------------------------------------------
		for (uint8_t n = 0; n < ids.size(); n++)
		{
			cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
			cv::drawFrameAxes(imageCopy, AR->getCameraMatrix640_480(), AR->getDistCoeffs640_480(), rvecs[n], tvecs[n], 0.1480 /2);  
		}

		//------------------------------------------------------------------------------------------------------------------------------------------------

	}

	return imageCopy;

}













int main()
{
	cv::VideoCapture inputVideo;
	cv::Mat inputImage;
	cv::Mat drawnImage;



	ARMarker AR;
	AR.videoSetup(&inputVideo);


	while (1)
	{
		inputImage = AR.getImageMat(inputVideo);
		drawnImage = AR.zahyouEstimation(&(AR.ARMarkerToEstimaitonPrm),inputImage,&AR);  
		AR.displayImage(drawnImage); //!!!画像表示のため10msの遅延関数が含まれているので注意!!!



		//パラメータ表示
		std::cout << "{x,y,z} =" << std::setprecision(3) << AR.ARMarkerToEstimaitonPrm.x << "," << AR.ARMarkerToEstimaitonPrm.y << "," << AR.ARMarkerToEstimaitonPrm.z << "\n";
		//std::cout << "{pitch,roll,yaw} =" << std::setprecision(3) << AR.ARMarkerToEstimaitonPrm.pitch << "," << AR.ARMarkerToEstimaitonPrm.roll << "," << AR.ARMarkerToEstimaitonPrm.roll << "\n";




	}



}
