#ifndef UTIL_H
#define UTIL_H


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <iostream>

#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>



using namespace cv;
using namespace std;


void ReadBmp(unsigned char *RGB,FILE *fp);


void Convert_rgb_yuv(unsigned char *RGB, unsigned char *YUV);

int WriteBmp(int width, int height, unsigned char *R,unsigned char *G,unsigned char *B, char *BmpFileName);

int convert_yuv_rgb(char*file,int width,int height);


void estar_interlace_crop_yuv420p(unsigned char *pdes, int width,int height, int crop_value);


    void savebmp(unsigned char * pdata, char * bmp_file, int width, int height )  ;

#endif











