cmake_minimum_required(VERSION 3.10)
project(AutoDrive10_23)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
link_libraries("/lib/libMVSDK.so")

include_directories(Lidar)

add_executable(AutoDrive10_23

        Lidar/C3iroboticsLidar.h
        Lidar/C3iroboticsLidarProtocol.h            Lidar/C3iroboticsLidar.cpp
        Lidar/CArcTime.h                            Lidar/CArcTime.cpp
        Lidar/CCountDown.h                          Lidar/CCountDown.cpp
        Lidar/CDeviceConnection.h                   Lidar/CDeviceConnection.cpp
        Lidar/CLidarPacket.h                        Lidar/CLidarPacket.cpp
        Lidar/CLidarPacketReceiver.h                Lidar/CLidarPacketReceiver.cpp
        Lidar/CLidarUnpacket.h                      Lidar/CLidarUnpacket.cpp
        Lidar/CLogUtitls.h                          Lidar/CSimulateSerial.cpp
        Lidar/CSerialConnection.h                   Lidar/CTime.cpp
        Lidar/CSimulateSerial.h                     Lidar/CSerialConnection.cpp
        Lidar/CTime.h
        Lidar/typedef.h



        main.cpp camera.cpp camera.h
        data.h SerialPort.cpp SerialPort.h
        fun.h Setter.cpp Setter.h Lidar.cpp Lidar.h)

find_package(OpenCV)
include_directories(${opencv_INCLUDE_DIRS})
target_link_libraries(AutoDrive10_23 ${OpenCV_LIBS})

find_package(Threads REQUIRED)
target_link_libraries(AutoDrive10_23 Threads::Threads)