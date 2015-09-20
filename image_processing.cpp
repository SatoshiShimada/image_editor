
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

#include "image_processing.h"

ImageProcessing::ImageProcessing(char *filename)
{
	inFileName = filename;
	src_img = cvLoadImage(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	dst_img = cvCloneImage(src_img);
	src_img_gray = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	dst_img_gray = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	//if(src_img->depth == IPL_DEPTH_8U || src_img->depth == IPL_DEPTH_8S) {
	if(src_img->nChannels == 1) {
		f_isGray = true;
	} else {
		f_isGray = false;
	}
}

void ImageProcessing::setFileName(char *f)
{
	outFileName = f;
}

char *ImageProcessing::getFileName(void)
{
	return (char *)outFileName.c_str();
}

int ImageProcessing::save(const char *filename)
{
	if(f_isGray) {
		cvCvtColor(dst_img_gray, dst_img, CV_GRAY2BGR);
	}
	cvSaveImage(filename, dst_img);
}
/*
 * return: 0 success
 *        -1 input image data error(need rgb image)
 */
int ImageProcessing::RGB2GRAY()
{
	if(f_isGray)
		return -1;
	cvCvtColor(src_img, dst_img_gray, CV_BGR2GRAY);
	src_img_gray = cvCloneImage(dst_img_gray);
	f_isGray = true;
	return 0;
}

/*
 * param[in] thresh: threshold (0 <= thresh <= 255)
 * return: 0 success
 *        -1 threshold value error(not range)
 *        -2 input image data error(need grayscale)
 */
int ImageProcessing::Threshold(int thresh)
{
	if(thresh < 0 || 255 < thresh)
		return -1;
	if(!f_isGray) {
		//return -2;
		this->RGB2GRAY();
	}
	cvThreshold(src_img_gray, dst_img_gray, thresh, 255, CV_THRESH_BINARY);
	return 0;
}
