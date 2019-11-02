//
// Created by shilei on 19-10-24.
//

#include "Lidar.h"
#include "C3iroboticsLidar.h"
#include "CSerialConnection.h"

void Lidar::init(int opt_com_baudrate,std::string opt_com_path)
{
    serial_connect.setBaud(opt_com_baudrate);
    serial_connect.setPort(opt_com_path.c_str());
    if(serial_connect.openSimple())
    {
        printf("[AuxCtrl] Open serail port sucessful!\n");
        printf("baud rate:%d\n",serial_connect.getBaud());
    }
    else
    {
        printf("[AuxCtrl] Open serail port %s failed! \n", opt_com_path.c_str());
    }

    printf("C3iroboticslidar connected\n");
    robotics_lidar.initilize(&serial_connect);
}

void Lidar::update()
{
    ld::TLidarGrabResult result=robotics_lidar.getScanData();
    switch(result)
    {
        case ld::LIDAR_GRAB_ING:
        case ld::LIDAR_GRAB_ELSE:
        case ld::LIDAR_GRAB_ERRO:
            //printf("[Main] LIDAR_GRAB!\n");
            //robotics_lidar.initilize(&serial_connect);
            break;
        case ld::LIDAR_GRAB_SUCESS:
        {
            lidar_scan=robotics_lidar.getLidarScan();
            size_t lidar_scan_size=lidar_scan.getSize();
            send_lidar_scan_data.resize(lidar_scan_size);
            RslidarDataComplete one_lidar_data;
            for (size_t i = 0; i < lidar_scan_size; i++) {
                one_lidar_data.signal = lidar_scan.signal[i];
                one_lidar_data.angle = lidar_scan.angle[i];
                one_lidar_data.distance = lidar_scan.distance[i];
                send_lidar_scan_data[i] = one_lidar_data;
                //printf("lidar_scan.angle=%f,lidar_scan.distance=%f\n", lidar_scan.angle[i],lidar_scan.distance[i]);
            }

        }
    }
}
