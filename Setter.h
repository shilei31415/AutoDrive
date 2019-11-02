//
// Created by shilei on 19-10-14.
//

#ifndef NOBODYCAR_SETTER_H
#define NOBODYCAR_SETTER_H

#include <opencv2/opencv.hpp>
class Setter {
public:
    Setter();
    cv::Mat mask;
    cv::Mat TransMat;
private:
    void make_mask();

};


#endif //NOBODYCAR_SETTER_H