//
// Created by shilei on 19-10-23.
//

//存储本函数所需全局变量

#ifndef AUTODRIVE10_23_DATA_H
#define AUTODRIVE10_23_DATA_H

#include <mutex>

#define STOP 2
#define CHANGE 1
#define GO_ON 0

static std::mutex Mutex;

static struct data
{
    double angle=0;
    double distance=0;
    int flag=0;
} sendata;

//图像平均亮度
static double mat_av=0;
//前方点的个数
static int front_num=0;
static int left_num=0;
static int right_num=0;

#endif //AUTODRIVE10_23_DATA_H
