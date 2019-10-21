#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;
Mat drawing;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;


// threshold
int threshold_value = 155;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

//erosion+dilation
int erosion_elem = 0;
int erosion_size = 9;
int dilation_elem = 0;
int dilation_size = 5;
int const max_elem = 2;
int const max_kernel_size = 21;

//opening
int morph_elem = 0;
int morph_size = 6;
int morph_operator = 0;
int const max_operator = 4;

//countertrack
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void* );



static void Threshold_Demo( int, void* )
{
    threshold( dst, dst, threshold_value, max_binary_value, threshold_type );    
}


void Erosion( int, void* )
{
	int erosion_type;
	if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
	else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
	else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
	Mat element = getStructuringElement( erosion_type,
		                               Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		                               Point( erosion_size, erosion_size ) );
	erode( dst, dst, element );

}


void Dilation( int, void* )
{
	int dilation_type;
	if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
	else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
	else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
	Mat element = getStructuringElement( dilation_type,
		                               Size( 2*dilation_size + 1, 2*dilation_size+1 ),
		                               Point( dilation_size, dilation_size ) );
	dilate( dst, dst, element );
}


void Morphology_Operations( int, void* )
{
	int operation = morph_operator + 2;
	Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
	morphologyEx( dst, dst, operation, element );
}


void thresh_callback(int, void* )
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny( dst, canny_output, thresh, thresh*2, 3 );
	findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	for( size_t i = 0; i< contours.size(); i++ )
	{
	   Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	   drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
	}
	namedWindow( "Contours", WINDOW_NORMAL );
	resizeWindow( "Contours", 600, 600 );
	imshow( "Contours", drawing );
	imwrite( "Out5_Contours.jpg", drawing );
}


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
	

	dst.create( src.size(), src.type() );

	/// Convert the image to grayscale
	cvtColor( src, src_gray, CV_BGR2GRAY );
	namedWindow("Color To Gray", WINDOW_NORMAL );
	resizeWindow("Color To Gray", 600, 600);
	imshow("Color To Gray", src_gray);
	imwrite( "Out1_ColorToGray.jpg", src_gray );


	/// Gaussian Filtering
	for ( int i = 1; i < 31; i = i + 2 ){ 
		GaussianBlur( src_gray, dst, Size( i, i ), 0, 0 );
	}
	namedWindow("After Gaussian", WINDOW_NORMAL );
	resizeWindow("After Gaussian", 600, 600);
	imshow("After Gaussian", dst);
	imwrite( "Out2_Gaussian.jpg", dst );
	
	
	///  Thresholding
	Threshold_Demo( 0, 0 );
    namedWindow( "After Threshold", WINDOW_NORMAL );
    resizeWindow( "After Threshold", 600, 600 );
    imshow( "After Threshold", dst );
    imwrite( "Out3_Threshold.jpg", dst );
	
	
	/// Morphological Processing
	
	
	/// Erosion
	cvMoveWindow( "Dilation Demo", src.cols, 0 );
	Erosion( 0, 0 );
	namedWindow( "Erosion Demo", WINDOW_NORMAL );
	resizeWindow( "Erosion Demo", 600, 600 );
	imshow( "Erosion Demo", dst );
	imwrite( "Out4_Erosion.jpg", dst );
	
	
	/// Dilation
	Dilation( 0, 0 );
	namedWindow( "Dilation Demo", WINDOW_NORMAL );
	resizeWindow( "Dilation Demo", 600, 600 );
	imshow( "Dilation Demo", dst );
	imwrite( "Out4_Dilation.jpg", dst );
	
	
	/// Opening
	Morphology_Operations( 0, 0 );
	namedWindow( "Opening Demo", WINDOW_NORMAL );
	resizeWindow( "Opening Demo", 600, 600 );
	imshow( "Opening Demo", dst );
	imwrite( "Out4_Opening.jpg", dst );
	
	
	/// Counter Tracking
	thresh_callback( 0, 0 );
  
  
	waitKey(0);

	return 0;
}
