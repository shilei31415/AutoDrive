//
// Created by shilei on 19-10-24.
//

#ifndef AUTODRIVE10_23_LIDAR_H
#define AUTODRIVE10_23_LIDAR_H

#include "CSerialConnection.h"
#include "C3iroboticsLidar.h"

#define ld everest::hwdrivers

typedef struct _rslidar_data
{
    _rslidar_data()
    {
        signal = 0;
        angle = 0.0;
        distance = 0.0;
    }
    uint8_t signal;
    float   angle;
    float   distance;
}RslidarDataComplete;

class Lidar {
public:
    ld::CSerialConnection serial_connect;
    ld::C3iroboticsLidar robotics_lidar;
    ld::TLidarScan lidar_scan;
    std::vector<RslidarDataComplete> send_lidar_scan_data;
    Lidar(){};
    void init(int opt_com_baudrate,std::string opt_com_path);
    void update();
};





#endif //AUTODRIVE10_23_LIDAR_H
