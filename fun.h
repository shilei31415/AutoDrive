//
// Created by shilei on 19-10-23.
//

#ifndef AUTODRIVE10_23_FUN_H
#define AUTODRIVE10_23_FUN_H


#include "data.h"
#include "camera.h"
#include "Setter.h"
#include "Lidar.h"
#include "SerialPort.h"
#include <ctime>

void Delay(int time)
{
    clock_t now=clock();
    while(clock()-now<time);
}
//摄像头负责寻线
//计算得到angle,distance,图像平均值

double average(cv::Mat&image,double &s)
{
    double m;
    cv::Mat mat_mean,mat_stddev;

    cv::meanStdDev(image,mat_mean,mat_stddev);
    m=mat_mean.at<double>(0,0);
    s=mat_stddev.at<double>(0,0);
    return m;
}

std::string getVideoName()
{
    time_t TimeValue;
    time(&TimeValue);
    char tmp[64];
    strftime(tmp, sizeof(tmp),"%Y-%m-%d-%H-%M-%S.avi",localtime(&TimeValue));
    return tmp;
}

void drawLine(float rho,float theta,cv::Point &pt1,cv::Point &pt2)
{
    double a=cos(theta),b=sin(theta);
    double x0=a*rho,y0=b*rho;
    pt1.x=cvRound(x0+10000*(-b));
    pt1.y=cvRound(y0+10000*(a));
    pt2.x=cvRound(x0-10000*(-b));
    pt2.y=cvRound(y0-10000*(a));
}

void findLine()
{
    std::string video_name=getVideoName();
    std::cout<<video_name<<std::endl;
    cv::VideoWriter writer(video_name,CV_FOURCC('M','J','P','G'),30,cv::Size(1280,1024),1);
    camera camera1;
    cv::Mat src,dst,tem;
    Setter setter;
    while(1)
    {
        camera1.getMat(src);
        cv::imshow("yuantu",src);
        writer<<src;

        cv::warpPerspective(src,dst,setter.TransMat,cv::Size(1280,1024));

        //输出
        dst.copyTo(tem);
        cv::line(tem,cv::Point(640,0),cv::Point(640,1024),cv::Scalar(0,255,0),1,8);
        cv::line(tem,cv::Point(0,512),cv::Point(1280,512),cv::Scalar(255,0,0),1,8);

        double s;
        cv::cvtColor(dst,dst,cv::COLOR_BGR2GRAY);
        static double m=average(dst,s);

        //易错 易错 易错 易错
        dst=dst>190;

        //代表通过二值化后的点的个数
        mat_av=average(dst,s);
        //输出
        cv::imshow("gray",dst);

        double x,angle;
        std::vector<cv::Vec2i> Xs;
        std::vector<cv::Vec2f> lines;
        cv::Canny(dst,dst,50,200,3);
        cv::HoughLines(dst,lines,1,CV_PI/180,150,0,0);
        for(int i=0;i<lines.size();i++)
        {
            float rho=lines[i][0],theta=lines[i][1];
            //qulingxing
            if(theta>1.2&&theta<2.2)
                continue;
            cv::Point pt1,pt2;
            drawLine(rho,theta,pt1,pt2);
            int x=cvRound(float((512-pt1.y)* (pt2.x-pt1.x))
                          /(pt2.y-pt1.y))+pt1.x;
            Xs.push_back(cv::Vec2i(x,i));
        }

        int Rmax=1280;
        int Lmax=0;
        for(int i=0;i<Xs.size();i++)
        {
            //std::cout<<Xs[i]<<"  ";
            if(Xs[i][0]-640>0) //为右线
            {
                if(Xs[i][0]<Rmax)
                    Rmax=Xs[i][0];
            }
            if(Xs[i][0]-640<0) //为左线
            {
                if(Xs[i][0]>Lmax)
                    Lmax=Xs[i][0];
            }
        }

        cv::Point ptL1,ptL2,ptR1,ptR2;
        for(int i=0;i<Xs.size();i++)
        {
            if(Xs[i][0]==Rmax)
            {
                int j=Xs[i][1];
                float rho=lines[j][0],theta=lines[j][1];
                drawLine(rho,theta,ptR1,ptR2);

                //输出
                cv::line(tem,ptR1,ptR2,cv::Scalar(0,0,255),5,8);
            }
            if(Xs[i][0]==Lmax)
            {
                int j=Xs[i][1];
                float rho=lines[j][0],theta=lines[j][1];
                drawLine(rho,theta,ptL1,ptL2);

                //输出
                cv::line(tem,ptL1,ptL2,cv::Scalar(0,0,255),5,8);

            }
        }

        cv::Point pt1,pt2,pt3,pt4,PT5,PT6;
        pt1.x=cvRound((0-ptL1.y)*(ptL2.x-ptL1.x)/double(ptL2.y-ptL1.y)+ptL1.x);
        pt1.y=0;
        pt2.x=cvRound((1024-ptL1.y)*(ptL2.x-ptL1.x)/double(ptL2.y-ptL1.y)+ptL1.x);
        pt2.y=1024;
        pt3.x=cvRound((0-ptR1.y)*(ptR2.x-ptR1.x)/double(ptR2.y-ptR1.y)+ptR1.x);
        pt3.y=0;
        pt4.x=cvRound((1024-ptR1.y)*(ptR2.x-ptR1.x)/double(ptR2.y-ptR1.y)+ptR1.x);
        pt4.y=1024;

        PT5=(pt1+pt3)/2,PT6=(pt2+pt4)/2;
        //输出
        cv::line(tem,PT5,PT6,cv::Scalar(255,255,0),1,8);
        x=double((1900-PT5.y)*(PT6.x-PT5.x))
                /(PT6.y-PT5.y)+PT5.x;
        angle=atan(double(pt2.y-pt1.y)/(pt2.x-pt1.x));

//        if(angle<0)
//            angle=(angle+CV_PI/2)*(180/CV_PI)*(-1);
//        else angle=(CV_PI/2-angle)*(180/CV_PI);

        if(x>=1280||x<=-1280)
            x=640;

        sendata.angle=angle;
        sendata.distance=x-640;

        //输出
        cv::imshow("xiaoguo",tem);
        cv::waitKey(1);
    }
}

void getLidardata(std::string path)
{

    Lidar lidar;
    lidar.init(230400,path);
    while(1)
    {
        lidar.update();
        right_num=0;
        left_num=0;
        front_num=0;
        //判断是否由障碍物
        for(int i=0;i<lidar.send_lidar_scan_data.size();i++)
        {
            RslidarDataComplete one_lidar_data=lidar.send_lidar_scan_data[i];
            if(one_lidar_data.angle>250&&one_lidar_data.angle<275)
            {

                std::cout<<"                                "<<one_lidar_data.angle<<"       "<<one_lidar_data.distance<<std::endl;
                double angle=one_lidar_data.angle*CV_PI/180,distance=one_lidar_data.distance;
                //距离过近靠右
                /*if(distance<0.7&&angle>10)
                    //sendata.distance+=sin(angle);
                    right_num++;
                //距离过近靠左
                else if(distance<0.07&&angle>10)
                    //sendata.distance+=sin(angle);
                    left_num++;
                else*/ if(distance<1&&distance>0.1)
                    front_num++;


            }
            if(one_lidar_data.angle>275&&one_lidar_data.angle<280)
            {
                if(one_lidar_data.distance<0.2&&one_lidar_data.distance>0.1)
                    left_num++;
            }

            if(one_lidar_data.angle>245&&one_lidar_data.angle<250)
            {
                if(one_lidar_data.distance<0.2&&one_lidar_data.distance>0.1)
                    right_num++;
            }

        }

        lidar.send_lidar_scan_data.clear();
    }
}

#endif //AUTODRIVE10_23_FUN_H
