#ifndef _screen_h
#define _screen_h

#include <bits/stdc++.h>
#include <unistd.h>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv/highgui.h>

using namespace cv;
using namespace std;

struct BGR
{
    uchar blue;
    uchar green;
    uchar red;
};

class Screen
{
    int height;
    int width;
    Mat pImgData;

public:
    bool finish;
    Screen(int h, int w)
    {
        height = h;
        width = w;
        finish = false;
        pImgData = Mat::zeros(w, h, CV_8UC3);
    }

    bool SetPixel(int x, int y, int COLOR = 0)
    {
        pImgData.at<Vec3b>(y, x) = {0, 255, 255};
        return true;
    }

    Scalar getPixel(int x, int y)
    {
        return pImgData.at<Vec3b>(y, x);
    }

    void display()
    {
        namedWindow("screen", CV_WINDOW_AUTOSIZE);
        imshow("screen", pImgData);
    }

    void clear()
    {
        pImgData = Mat::zeros(width, height, CV_8UC3);
    }

    bool update()
    {
        imshow("screen", pImgData);
        if (cv::waitKey(50) == 27)
            finish = true;
    }
};

#endif
