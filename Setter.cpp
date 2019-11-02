//
// Created by shilei on 19-10-14.
//

#include "Setter.h"
#include<opencv2/opencv.hpp>
Setter::Setter() {
    make_mask();

    cv::FileStorage Settingfile("para.yaml",cv::FileStorage::READ);
    //判断文件是否打开成功.

    Settingfile["TransMat"]>>TransMat;
}

void Setter::make_mask()
{
    mask=cv::Mat::zeros(cv::Size(1280,1024),CV_8UC1);
    cv::line(mask,cv::Point(200,0),cv::Point(200,1024),cv::Scalar(255,255,255),250);
    cv::line(mask,cv::Point(640,300),cv::Point(1280,1024),cv::Scalar(255,255,255),250);
    cv::line(mask,cv::Point(0,1023),cv::Point(1280,1023),cv::Scalar(255,255,255),6);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(mask,contours,hierarchy,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);
    //std::cout<<contours.size()<<std::endl;
    //for(int i=0;i<contours.size();i++)
    {
        cv::drawContours(mask, contours, 0, cv::Scalar(255, 255, 255), -1, 8);
        //cv::imshow("mask", mask);
        //cv::waitKey(0);
    }
    //cv::destroyAllWindows();
}