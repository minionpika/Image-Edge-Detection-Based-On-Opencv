#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

Mat src, erosion_dst, dilation_dst, dst;

int erosion_elem = 0;
int erosion_size = 9;
int dilation_elem = 0;
int dilation_size = 5;
int const max_elem = 2;
int const max_kernel_size = 21;


int morph_elem = 0;
int morph_size = 6;
int morph_operator = 0;
int const max_operator = 2;


void Erosion( int, void* )
{
	int erosion_type;
	if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
	else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
	else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement( erosion_type,
		                               Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		                               Point( erosion_size, erosion_size ) );

	erode( src, erosion_dst, element );
	resizeWindow( "Erosion Demo", 600, 600 );
	imshow( "Erosion Demo", erosion_dst );
	imwrite( "Out_Erosion.jpg", erosion_dst );
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

	dilate( erosion_dst, dilation_dst, element );
	resizeWindow( "Dilation Demo", 600, 600 );
	imshow( "Dilation Demo", dilation_dst );
	imwrite( "Out_Dilation.jpg", dilation_dst );
}


void Morphology_Operations( int, void* )
{
	int operation = morph_operator + 2;
	Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

	morphologyEx( dilation_dst, dst, operation, element );
	resizeWindow( "Opening Demo", 600, 600 );
	imshow( "Opening Demo", dst );
	imwrite( "Out_Opening.jpg", dst );
}



int main( int argc, char** argv )
{
	src = imread( argv[1] );

	if( !src.data ) return -1;

	namedWindow( "Erosion Demo", WINDOW_NORMAL );
	namedWindow( "Dilation Demo", WINDOW_NORMAL );
	namedWindow( "Opening Demo", WINDOW_NORMAL );

	cvMoveWindow( "Dilation Demo", src.cols, 0 );


	/// Default start
	Erosion( 0, 0 );
	Dilation( 0, 0 );
	Morphology_Operations( 0, 0 );

	waitKey(0);
	return 0;
}

