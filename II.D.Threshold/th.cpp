#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int threshold_value = 150;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
Mat src, src_gray, dst;


const char* trackbar_type = "0: Binary\n1: BinaryInverted\n2: Truncate\n3: To Zero\n4: To Zero Inverted";


static void Threshold_Demo( int, void* )
{
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
	resizeWindow( "Threshold Demo", 600, 600);
    imshow( "Threshold Demo", dst );
    imwrite( "Out_BinaryThreshold.jpg", dst );
}


int main( int argc, char** argv )
{
    src = imread( argv[1] );
    if (src.empty()) return -1;
    
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); 
    namedWindow( "Threshold Demo", WINDOW_NORMAL );
    
    createTrackbar( trackbar_type,
                    "Threshold Demo", &threshold_type,
                    max_type, Threshold_Demo );
 
 
    Threshold_Demo( 0, 0 );
 
    waitKey();
    return 0;
}
