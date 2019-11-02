#include <iostream>
#include "camera.h"
#include "fun.h"
#include <thread>
#include <mutex>
#include "SerialPort.h"


int main()
{
    SerialPort STM32;
    STM32.Open("/dev/SerialPort",115200);
    //加入线程1 不断更新angle distance
    std::thread line1(findLine);
    std::thread line2(getLidardata,"/dev/Lidar");


    unsigned char a[2]={0xff,0xfe};

    while(1)
    {
        //cout<<right_num<<"  "<<left_num<<"  "<<front_num<<endl;
        //std::cout<<mat_av<<std::endl;

//        if(mat_av>100&&front_num<5)
//            sendata.flag=STOP;


//        if(left_num>20)
//            sendata.distance-=100;
//
//        if(right_num>20)
//            sendata.distance+=100;
        cout<<"平均值"<<mat_av<<endl;
        sendata.flag=GO_ON;
        if(mat_av>40&&front_num<14)
            sendata.flag=STOP;
        if(front_num>14)
            sendata.flag=CHANGE;
        if(left_num>5)
            sendata.angle=1;
        if(right_num>5)
            sendata.angle=-1;

        try {
            std::cout << "前方" << front_num << std::endl;
            STM32.writeBuffer(a, 1);
            STM32.writeBuffer(sendata.angle, sendata.distance, sendata.flag);
            STM32.writeBuffer(a + 1, 1);
            STM32.Open("/dev/SerialPort",115200);
            Delay(20);
        }
        catch(exception&e)
        {
            std::cout<<e.what();
            STM32.Open("/dev/SerialPort",115200);
        }


    }
    line1.join();
    line2.join();
    return 0;
}