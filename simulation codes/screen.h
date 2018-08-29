#ifndef _screen_h
#define _screen_h

#include <bits/stdc++.h>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv/highgui.h>
using namespace cv;
using namespace std;
class Screen
{
    int height;
    int width;
    Mat pImgData;

  public:
    Screen(int h, int w)
    {
        height = h;
        width = w;
        pImgData = Mat::zeros(w, h, CV_8UC3);
    }

    bool SetPixel(int x, int y, int COLOR = 0)
    {
        pImgData.at<Vec3b>(y, x) = 255, 0, 0;
        return true;
    }

    void display()
    {
        namedWindow("screen", CV_WINDOW_AUTOSIZE);
        imshow("screen", pImgData);
        waitKey(0);
    }
};

#endif
