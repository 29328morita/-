#include "zahyouEstimation.h"
#pragma once


typedef struct
{
    float x, y, z, yaw, pitch, roll;
}ARMarkerToPoseEstimationPrm;


//typedef struct
//{
//    int8_t markerId;
//    float x, y;
//}markerPosition;


class markerPosition
{

    public:
        int8_t markerId;
        float x, y;
        markerPosition(int8_t id, float MarkerX, float MarkerY)
        {
            markerId = id;
            x = MarkerX;
            y = MarkerY;
        }

};



//camera param
const  cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 939.58838, 0, 719.5, 0, 939.58838, 539.5, 0, 0, 1);
const  cv::Mat distCoeffs = (cv::Mat_<double>(1, 5) << -0.23275, 0.144761, 0, 0, 0);
const  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);





ARMarkerToPoseEstimationPrm PrmInit(float x0, float y0, float z0) {
    ARMarkerToPoseEstimationPrm Prm;
    Prm.x = x0;
    Prm.y = y0;
    Prm.z = z0;
    Prm.yaw = 0;
    Prm.pitch = 0;
    Prm.roll = 0;


    return Prm;

}


cv::Mat getImageMat(cv::VideoCapture inputVideo)
{
    cv::Mat image;

    if (inputVideo.grab()) {
        inputVideo.retrieve(image);
    }


    return image;
}




void  zahyouEstimation(ARMarkerToPoseEstimationPrm* Prm, markerPosition *MP,cv::Mat image) {



    cv::Mat imageCopy, outputArry;
    image.copyTo(imageCopy);
    std::vector<int> ids;



    std::vector<std::vector<cv::Point2f>> corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);


    // if at least one marker detected
    if (ids.size() > 0) {
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
        std::vector<cv::Vec3d> rvecs, tvecs;
        cv::aruco::estimatePoseSingleMarkers(corners, 0.14800, cameraMatrix, distCoeffs, rvecs, tvecs, outputArry);


        // draw axis for each marker
        for (int i = 0; i < ids.size(); i++)
            cv::drawFrameAxes(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);  //evecs回転　tvecs並進



        //MarkerToCameraPosition(マーカーからの距離)



        //rvecs,tvces --  std::vector → cv::Mat  (y,x)

        cv::Mat rvecs_Mat = (cv::Mat_<float>(1, 3) << rvecs.at(0)[0], rvecs.at(0)[1], rvecs.at(0)[2]);
        cv::Mat tvecs_Mat = (cv::Mat_<float>(1, 3) << tvecs.at(0)[0], tvecs.at(0)[1], tvecs.at(0)[2]);
        cv::Mat vector3_0 = (cv::Mat_<float>(1, 3) << 0, 0, 0);


        //初期化
        cv::Mat R = cv::Mat::eye(3, 3, CV_32F), Rt = cv::Mat::eye(3, 3, CV_32F);
        cv::Mat MarkerToCameraPosition;// = (cv::Mat_<float>(1, 3) << 0, 0, 0);


        //ロドリゲス変換 カメラ座標系のrvecsをマーカー座標系に変換------------------------------------------------------
        cv::Rodrigues(rvecs_Mat, Rt);
        R = Rt.t();


         //エラー回避の関係で　縦ベクトル+他0の3*3
        tvecs_Mat = (cv::Mat_<float>(3, 3) << tvecs.at(0)[0], 0, 0, tvecs.at(0)[1], 0, 0, tvecs.at(0)[2], 0, 0);

        MarkerToCameraPosition = (-R) * (tvecs_Mat);



        //-------------------------------------------------------------------------------------------------------------------


        //マーカーidからマーカー固有のフィールド座標を付与
        //switch


        Prm->x = MarkerToCameraPosition.at<float>(0, 0);
        Prm->y = MarkerToCameraPosition.at<float>(1, 0);
        Prm->z = MarkerToCameraPosition.at<float>(2, 0);
        Prm->roll = std::atan2(static_cast<float>(-(R.at<float>(2, 1))), static_cast<float>(R.at<float>(2, 2))); //コンパイルエラー対策
        Prm->pitch = std::asin(static_cast<float>(R.at<float>(2, 0)));
        Prm->yaw = std::atan2(static_cast<float>(-(R.at<float>(1, 0))), static_cast<float>(R.at<float>(0, 0)));






    }


    cv::imshow("out", imageCopy);


    char key = (char)cv::waitKey(10);








}



int main()
{

    //camera------------------------------------------------------------------
    //camera
    cv::VideoCapture inputVideo;
    cv::Mat image;



    //camera
    inputVideo.open(0);
    inputVideo.set(cv::CAP_PROP_FPS, 15);           //カメラFPSを60FPSに設定
    inputVideo.set(cv::CAP_PROP_FRAME_WIDTH, 1280);// カメラ画像の横幅を1280に設定
    inputVideo.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // カメラ画像の縦幅を720に設定, 


    //マーカー座標コンストラクタ
    markerPosition markerPosition[MarkerIdsNumber] = 
    {
        {0,Marker00_x,Marker00_y},
        {1,Marker01_x,Marker01_y},
        {2,Marker02_x,Marker02_y},
        {3,Marker03_x,Marker03_y},
        {4,Marker04_x,Marker04_y},
        {5,Marker05_x,Marker05_y},
        {6,Marker06_x,Marker06_y},
        {7,Marker07_x,Marker07_y},
        {8,Marker08_x,Marker08_y},       
        {9,Marker09_x,Marker09_y},
        {10,Marker10_x,Marker10_y},
        {11,Marker11_x,Marker11_y},
        {12,Marker12_x,Marker12_y}

    };






    



    ARMarkerToPoseEstimationPrm zahyouPrm = PrmInit(0, 0, 0);

    while (1)
    {
        image = getImageMat(inputVideo);
        zahyouEstimation(&zahyouPrm, markerPosition, image);

        std::cout << "({x,y,z} " << zahyouPrm.x << "," << zahyouPrm.y << "," << zahyouPrm.z << "},{\n"; 
//        std::cout<<"(r, p, y)=("<<zahyouPrm.roll << "," << zahyouPrm.pitch << "," << zahyouPrm.yaw << "),{\n";
    }




}


