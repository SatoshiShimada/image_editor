
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

#include <iostream>
#include <string>

class ImageProcessing {

private:
	bool f_isGray = false;
	//char *outFileName = 0;
	//char *inFileName  = 0;
	std::string outFileName;
	std::string inFileName;
	IplImage *src_img = 0;
	IplImage *dst_img = 0;
	IplImage *src_img_gray = 0;
	IplImage *dst_img_gray = 0;

public:
	ImageProcessing(char *);

	int save(const char *);
	int RGB2GRAY();
	int Threshold(int);
	void setFileName(char *);
	char *getFileName(void);

	const char *tmpFileName = "tmp.png";
};
