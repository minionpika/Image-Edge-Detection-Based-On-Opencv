#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;


int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;


int main( int argc, char** argv )
{
	
	src = imread( argv[1] );
	dst = src.clone();
	

	/// Homogeneous blur
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{ 
		blur( src, dst, Size( i, i ), Point(-1,-1) );
	}
	namedWindow( "Homogeneous blur", WINDOW_NORMAL );
	resizeWindow( "Homogeneous blur", 600, 600);	
	imshow( "Homogeneous blur", dst );
	imwrite( "Out_HomogeneousBlur.jpg", dst );


	/// Gaussian blur
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{ 
		GaussianBlur( src, dst, Size( i, i ), 0, 0 );	
	}
	namedWindow( "Gaussian blur", WINDOW_NORMAL );
	resizeWindow( "Gaussian blur", 600, 600);
	imshow( "Gaussian blur", dst );
	imwrite( "Out_GaussianBlur.jpg", dst );
	
	
	/// Median blur
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{ 
		medianBlur ( src, dst, i );
	}
	namedWindow( "Median blur", WINDOW_NORMAL );
	resizeWindow( "Median blur", 600, 600);
	imshow( "Median blur", dst );
	imwrite( "Out_MedianBlur.jpg", dst );

	
	/// Bilateral Filter
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{ 
		bilateralFilter ( src, dst, i, i*2, i/2 );
	}
	namedWindow( "Bilateral Blur", WINDOW_NORMAL );
	resizeWindow( "Bilateral Blur", 600, 600);
	imshow( "Bilateral Blur", dst );
	imwrite( "Out_BilateralBlur.jpg", dst );
		
	waitKey(0);
	return 0;
}

