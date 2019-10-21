#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/// Global variables

Mat src, src_gray;

int main( int argc, char** argv )
{
	/// Load an image
	src = imread( argv[1] );

	if( !src.data )	return -1;
	
	// Output image
	Mat imgOut = src.clone();
	namedWindow("Source", WINDOW_NORMAL );
	resizeWindow("Source", 600, 600);
	imshow("Source", src);
	

	/// Create a matrix of the same type and size as src (for dst)
	src_gray.create( src.size(), src.type() );

	/// Convert the image to grayscale
	cvtColor( src, src_gray, CV_BGR2GRAY );
	namedWindow("Color To Gray", WINDOW_NORMAL );
	resizeWindow("Color To Gray", 600, 600);
	imshow("Color To Gray", src_gray);
	
	imwrite( "out.jpg", src_gray );
	
	waitKey(0);
  	return 0;
	
}
