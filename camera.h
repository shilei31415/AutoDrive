//
// Created by shilei on 19-10-23.
//

#ifndef AUTODRIVE10_23_CAMERA_H
#define AUTODRIVE10_23_CAMERA_H

#include "CameraApi.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

class camera {
    int                     iCameraCounts = 1;
    int                     iStatus=-1;
    tSdkCameraDevInfo       tCameraEnumList;
    int                     hCamera;
    tSdkCameraCapbility     tCapability;      //设备描述信息
    tSdkFrameHead           sFrameInfo;
    BYTE*			        pbyBuffer;
    int                     iDisplayFrames = 10000;
    IplImage *iplImage = NULL;
    int                     channel=3;
    unsigned char           * g_pRgbBuffer;

public:
    camera();
    void getMat(cv::Mat & Image);
    ~camera();
};

#endif //AUTODRIVE10_23_CAMERA_H
