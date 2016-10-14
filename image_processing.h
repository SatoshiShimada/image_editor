
/*
 * The Image Processing class for Image Editor.
 * Using OpenCV.
 *
 * Author: Satoshi SHIMADA
 * Date: Sep 20, 2015
 * Last-update: Oct 14, 2016
 */

#include "cv.h"
#include "highgui.h"
#include "ctype.h"

#include <iostream>
#include <string>

class ImageProcessing {

private:
	bool f_isGray;
	std::string outFileName;
	std::string inFileName;
	IplImage *src_img;
	IplImage *dst_img;
	IplImage *src_img_gray;
	IplImage *dst_img_gray;

public:
	ImageProcessing(char *);

	int save(const char *);
	int RGB2GRAY();
	int Threshold(int);
	void setFileName(char *);
	char *getFileName(void);

	const char *tmpFileName;
};

